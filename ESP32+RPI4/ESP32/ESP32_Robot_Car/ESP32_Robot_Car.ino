#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <cstring>
#include <ESPAsyncWebServer.h>
#include "pin_defined.h"
#include "control_page.h"
#include "Speed_PWM.h"

#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

const char* ssid     = "Robot_car01";
const char* password = "987654321";

// Set web server port number to 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

bool ledState = true;
struct MOTOR_PINS
{
  int pinIN1;
  int pinIN2;    
};

std::vector<MOTOR_PINS> motorPins = 
{
  {16, 17},  //FRONT_RIGHT_MOTOR
  {18, 19},  //BACK_RIGHT_MOTOR
  {27, 26},  //FRONT_LEFT_MOTOR
  {25, 32},  //BACK_LEFT_MOTOR   
};

void rotateMotor(int motorNumber, int motorDirection)
{
  if (motorDirection == FORWARD)
  {
    digitalWrite(motorPins[motorNumber].pinIN1, HIGH);
    digitalWrite(motorPins[motorNumber].pinIN2, LOW);    
  }
  else if (motorDirection == BACKWARD)
  {
    digitalWrite(motorPins[motorNumber].pinIN1, LOW);
    digitalWrite(motorPins[motorNumber].pinIN2, HIGH);     
  }
  else
  {
    digitalWrite(motorPins[motorNumber].pinIN1, LOW);
    digitalWrite(motorPins[motorNumber].pinIN2, LOW);       
  }

  //pinMode(basePin, OUTPUT);
  //pinMode(ledPin, OUTPUT);

}

//void processCarMovement(String inputValue) Sang
void processCarMovement(int inputValue)
{
  //Serial.printf("Got value as %s %d\n", inputValue.c_str(), inputValue.toInt());  Sang
  Serial.printf("Got value as %d\n", inputValue); 

  
  //switch(inputValue.toInt())
   switch(inputValue)
  {

    case UP:
      rotateMotor(FRONT_RIGHT_MOTOR, FORWARD);
      rotateMotor(BACK_RIGHT_MOTOR, FORWARD);
      rotateMotor(FRONT_LEFT_MOTOR, FORWARD);
      rotateMotor(BACK_LEFT_MOTOR, FORWARD);                  
      break;
  
    case DOWN:
      rotateMotor(FRONT_RIGHT_MOTOR, BACKWARD);
      rotateMotor(BACK_RIGHT_MOTOR, BACKWARD);
      rotateMotor(FRONT_LEFT_MOTOR, BACKWARD);
      rotateMotor(BACK_LEFT_MOTOR, BACKWARD);   
      break;
  
    case LEFT:
      rotateMotor(FRONT_RIGHT_MOTOR, FORWARD);
      rotateMotor(BACK_RIGHT_MOTOR, BACKWARD);
      rotateMotor(FRONT_LEFT_MOTOR, BACKWARD);
      rotateMotor(BACK_LEFT_MOTOR, FORWARD);   
      break;
  
    case RIGHT:
      rotateMotor(FRONT_RIGHT_MOTOR, BACKWARD);
      rotateMotor(BACK_RIGHT_MOTOR, FORWARD);
      rotateMotor(FRONT_LEFT_MOTOR, FORWARD);
      rotateMotor(BACK_LEFT_MOTOR, BACKWARD);  
      break;
  
    case UP_LEFT:
      rotateMotor(FRONT_RIGHT_MOTOR, FORWARD);
      rotateMotor(BACK_RIGHT_MOTOR, STOP);
      rotateMotor(FRONT_LEFT_MOTOR, STOP);
      rotateMotor(BACK_LEFT_MOTOR, FORWARD);  
      break;
  
    case UP_RIGHT:
      rotateMotor(FRONT_RIGHT_MOTOR, STOP);
      rotateMotor(BACK_RIGHT_MOTOR, FORWARD);
      rotateMotor(FRONT_LEFT_MOTOR, FORWARD);
      rotateMotor(BACK_LEFT_MOTOR, STOP);  
      break;
  
    case DOWN_LEFT:
      rotateMotor(FRONT_RIGHT_MOTOR, STOP);
      rotateMotor(BACK_RIGHT_MOTOR, BACKWARD);
      rotateMotor(FRONT_LEFT_MOTOR, BACKWARD);
      rotateMotor(BACK_LEFT_MOTOR, STOP);   
      break;
  
    case DOWN_RIGHT:
      rotateMotor(FRONT_RIGHT_MOTOR, BACKWARD);
      rotateMotor(BACK_RIGHT_MOTOR, STOP);
      rotateMotor(FRONT_LEFT_MOTOR, STOP);
      rotateMotor(BACK_LEFT_MOTOR, BACKWARD);   
      break;
  
    case TURN_RIGHT: //TURN_LEFT
      rotateMotor(FRONT_RIGHT_MOTOR, FORWARD);
      rotateMotor(BACK_RIGHT_MOTOR, FORWARD);
      rotateMotor(FRONT_LEFT_MOTOR, BACKWARD);
      rotateMotor(BACK_LEFT_MOTOR, BACKWARD);  
      break;
  
    case TURN_LEFT://TURN_RIGHT
      rotateMotor(FRONT_RIGHT_MOTOR, BACKWARD);
      rotateMotor(BACK_RIGHT_MOTOR, BACKWARD);
      rotateMotor(FRONT_LEFT_MOTOR, FORWARD);
      rotateMotor(BACK_LEFT_MOTOR, FORWARD);   
      break;
  
    case STOP:
      rotateMotor(FRONT_RIGHT_MOTOR, STOP);
      rotateMotor(BACK_RIGHT_MOTOR, STOP);
      rotateMotor(FRONT_LEFT_MOTOR, STOP);
      rotateMotor(BACK_LEFT_MOTOR, STOP);    
      break;

     case 11:
     toggleLED();
     break;

  
    default:
      rotateMotor(FRONT_RIGHT_MOTOR, STOP);
      rotateMotor(BACK_RIGHT_MOTOR, STOP);
      rotateMotor(FRONT_LEFT_MOTOR, STOP);
      rotateMotor(BACK_LEFT_MOTOR, STOP);    
      break;
  }


}

void handleRoot(AsyncWebServerRequest *request) 
{
  request->send_P(200, "text/html", htmlHomePage);
}

void handleNotFound(AsyncWebServerRequest *request) 
{
    request->send(404, "text/plain", "File Not Found");
}


void onWebSocketEvent(AsyncWebSocket *server, 
                      AsyncWebSocketClient *client, 
                      AwsEventType type,
                      void *arg, 
                      uint8_t *data, 
                      size_t len) 
{                      
  switch (type) 
  {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      digitalWrite(basePin,HIGH); //drive for initial esp32 or manual control
      digitalWrite(ledPin,HIGH); //drive for initial esp32 or manual control

      ledState = 1;
      //client->text(getRelayPinsStatusJson(ALL_RELAY_PINS_INDEX));
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      //processCarMovement("0"); sang
      processCarMovement(0);
      break;
    case WS_EVT_DATA:
      AwsFrameInfo *info;
      info = (AwsFrameInfo*)arg;
      if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) 
      {
        std::string myData = "";
        myData.assign((char *)data, len); 

        std::string sub_str = myData.substr(0,5); // speed-200
         if (sub_str == "speed"){
          std::string sub_str2 = myData.substr(6,5);
          int val = stoi(sub_str2); // c++ sang converts the string argument str to an integer
           if (val > 255)
                val = 255;
            else if (val < 0)
                val = 0;
              //ledcWrite(0, val);
              update_speed(val);
             Serial.printf("PWM %d \n", val);
         }
         else if (sub_str == "contr"){
          std::string sub_str3 = myData.substr(8,2);
          int val1 = stoi(sub_str3); // c++ sang converts the string argument str to an integer
            processCarMovement(val1);     
         }
        //processCarMovement(myData.c_str());       
      }

      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
    default:
      break;  
  }
}

void setUpPinModes()
{
  for (int i = 0; i < motorPins.size(); i++)
  {
    pinMode(motorPins[i].pinIN1, OUTPUT);
    pinMode(motorPins[i].pinIN2, OUTPUT);  
    rotateMotor(i, STOP);  
  }
  pinMode(basePin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(MTL_PWM, OUTPUT);
  pinMode(MTR_PWM, OUTPUT);
  //digitalWrite(basePin, LOW); 
}


void setup(void) 
{
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable detector
  //pinMode(basePin, OUTPUT);
  setUpPinModes();
  Serial.begin(115200);
  digitalWrite(basePin, HIGH);
  digitalWrite(ledPin,HIGH);

  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", HTTP_GET, handleRoot);

  server.onNotFound(handleNotFound);
  
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);
  
  server.begin();
  Serial.println("HTTP server started");

  /**
    @PWM Setup
  */
  // Motor uses PWM Channel 8
  // ledcSetup(ledChannel, freq, resolution);
  ledcSetup(pwmChannel, freq, resolution);
  // ledcAttachPin(ledPin, ledChannel);
  ledcAttachPin(MTL_PWM, pwmChannel);
  ledcAttachPin(MTR_PWM, pwmChannel);
  // ledcWrite(ledChannel, dutyCycle);
  ledcWrite(0, 200); // initial setup

}

void loop() 
{
  ws.cleanupClients(); 
}

void toggleLED() {
  ledState = !ledState;
  digitalWrite(basePin, ledState ? HIGH : LOW);
  digitalWrite(ledPin, ledState ? HIGH : LOW);
}

