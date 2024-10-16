struct MOTOR_PINS
{
  int pinEn;  
  int pinIN1;
  int pinIN2;    
};

std::vector<MOTOR_PINS> motorPins = 
{
  {12, 13, 15},  //RIGHT_MOTOR Pins (EnA, IN1, IN2)
 {12, 14, 3},  //LEFT_MOTOR  Pins (EnB, IN3, IN4)
 
};
// 28June24 #define LIGHT_PIN 4

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define STOP 0

#define RIGHT_MOTOR 0
#define LEFT_MOTOR 1

#define FORWARD 1
#define BACKWARD -1

const int PWMFreq = 1000; /* 1 KHz */
const int PWMResolution = 8;
const int PWMSpeedChannel = 12; // change PWM to GPIO 12
const int PWMLightChannel = 4;

int slRead = 0;
int srRead = 0;

//Camera related constants
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

#define  SensorRIGHT            1  // RIGHT sensor 
#define  SensorLEFT             2  // LEFT sensor 
#define  ledPin                 4  // LED input
//https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2018/08/esp32-pinout-chip-ESP-WROOM-32.png?quality=100&strip=all&ssl=1


const char* ssid     = "robot_car_09";
const char* password = "123456789";

AsyncWebServer server(80);
AsyncWebSocket wsCamera("/Camera");
AsyncWebSocket wsCarInput("/CarInput");
uint32_t cameraClientId = 0;
