#include "esp_camera.h"
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <iostream>
#include <sstream>
#include "pin_define.h"
#include "index.h"

// Disable brownout detector to avoid resets
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "driver/rtc_io.h"

// Constants and Globals
const int frameInterval = 100;  // Frame interval in milliseconds (~10 FPS)
unsigned long lastFrameTime = 0;
int mode = 0;  // 0 = Manual, 1 = Autonomous
bool psramEnabled = false;  // Check for PSRAM availability

// Forward Declarations
void sendCameraPicture();
void setupCamera();
void moveCar(int inputValue);
void rotateMotor(int motorNumber, int motorDirection);

// Motor Control
void rotateMotor(int motorNumber, int motorDirection) {
  digitalWrite(motorPins[motorNumber].pinIN1, motorDirection == FORWARD);
  digitalWrite(motorPins[motorNumber].pinIN2, motorDirection == BACKWARD);
}

void moveCar(int inputValue) {
  switch (inputValue) {
    case UP:
      rotateMotor(RIGHT_MOTOR, FORWARD);
      rotateMotor(LEFT_MOTOR, FORWARD);
      break;
    case DOWN:
      rotateMotor(RIGHT_MOTOR, BACKWARD);
      rotateMotor(LEFT_MOTOR, BACKWARD);
      break;
    case LEFT:
      rotateMotor(RIGHT_MOTOR, FORWARD);
      rotateMotor(LEFT_MOTOR, BACKWARD);
      break;
    case RIGHT:
      rotateMotor(RIGHT_MOTOR, BACKWARD);
      rotateMotor(LEFT_MOTOR, FORWARD);
      break;
    default:
      rotateMotor(RIGHT_MOTOR, STOP);
      rotateMotor(LEFT_MOTOR, STOP);
      break;
  }
}

// WebSocket Handlers
void onCarInputWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_DATA) {
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if (info->final && info->opcode == WS_TEXT) {
      std::istringstream ss(std::string((char *)data, len));
      std::string key, value;
      std::getline(ss, key, ',');
      std::getline(ss, value, ',');
      int valueInt = atoi(value.c_str());

      if (key == "MoveCar" && mode == 0) moveCar(valueInt);
      else if (key == "Speed") ledcWrite(PWMSpeedChannel, mode == 0 ? valueInt : 90);
      else if (key == "Mode") { mode = valueInt; moveCar(STOP); }
      //else if (key == "led") digitalWrite(ledPin, valueInt);
      else if (key == "Light") ledcWrite(PWMLightChannel, valueInt);
    }
  }
}

void onCameraWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) cameraClientId = client->id();
  if (type == WS_EVT_DISCONNECT) cameraClientId = 0;
}

// Camera Setup and Capture
void setupCamera() {
camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    // Optimize frame size and quality to balance performance.
    config.frame_size = FRAMESIZE_VGA; // Adjust to FRAMESIZE_QVGA for faster stream
    config.jpeg_quality = 15; // 15 is a good tradeoff between quality and size
    config.fb_count = psramFound() ? 2 : 1; // Use two buffers if PSRAM is available


  if (esp_camera_init(&config) != ESP_OK) {
    Serial.println("Camera initialization failed.");
    return;
  }

  psramEnabled = psramFound();
  if (psramEnabled) heap_caps_malloc_extmem_enable(20000);

  sensor_t *s = esp_camera_sensor_get();
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
}

void sendCameraPicture() {
  if (!cameraClientId) return;
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) return;

  wsCamera.binary(cameraClientId, fb->buf, fb->len);
  esp_camera_fb_return(fb);
}

// Pin Setup
void setUpPinModes() {
  ledcSetup(PWMSpeedChannel, PWMFreq, PWMResolution);
  for (const auto &motor : motorPins) {
    pinMode(motor.pinEn, OUTPUT);
    pinMode(motor.pinIN1, OUTPUT);
    pinMode(motor.pinIN2, OUTPUT);
    ledcAttachPin(motor.pinEn, PWMSpeedChannel);
  }
  //pinMode(ledPin, OUTPUT);
  ledcSetup(PWMLightChannel, PWMFreq, PWMResolution);

  ledcAttachPin(ledPin, PWMLightChannel);
  
  moveCar(STOP);
}

// WiFi and Server Setup
void setupWiFiAndServer() {
  WiFi.softAP(ssid, password);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { request->send_P(200, "text/html", htmlHomePage); });
  server.onNotFound([](AsyncWebServerRequest *request) { request->send(404, "text/plain", "File Not Found"); });

  wsCamera.onEvent(onCameraWebSocketEvent);
  server.addHandler(&wsCamera);

  wsCarInput.onEvent(onCarInputWebSocketEvent);
  server.addHandler(&wsCarInput);

  server.begin();
  Serial.println("HTTP server started");
}

// Main Setup
void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);  // Disable brownout detector
  //Serial.begin(115200);

  setUpPinModes();
  setupWiFiAndServer();
  setupCamera();
}

// Main Loop
void loop() {
  //wsCamera.cleanupClients();
  //wsCarInput.cleanupClients();

  if (millis() - lastFrameTime >= frameInterval) {
    sendCameraPicture();
    lastFrameTime = millis();
  }

  if (mode == 1) {
    bool slRead = digitalRead(SensorLEFT);
    bool srRead = digitalRead(SensorRIGHT);

    if (!slRead && !srRead) moveCar(UP);
    else if (!slRead) { moveCar(LEFT); delay(300); }
    else if (!srRead) { moveCar(RIGHT); delay(300); }
    else moveCar(STOP);
  }
}
