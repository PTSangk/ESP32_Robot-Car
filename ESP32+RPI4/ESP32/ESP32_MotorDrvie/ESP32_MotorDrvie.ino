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


#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

struct MOTOR_PINS {
  int pinIN1;
  int pinIN2;
};

std::vector<MOTOR_PINS> motorPins = {
  { 16, 17 },  //FRONT_RIGHT_MOTOR
  { 18, 19 },  //BACK_RIGHT_MOTOR
  { 27, 26 },  //FRONT_LEFT_MOTOR
  { 25, 32 },  //BACK_LEFT_MOTOR
};

void rotateMotor(int motorNumber, int motorDirection) {
  if (motorDirection == FORWARD) {
    digitalWrite(motorPins[motorNumber].pinIN1, HIGH);
    digitalWrite(motorPins[motorNumber].pinIN2, LOW);
  } else if (motorDirection == BACKWARD) {
    digitalWrite(motorPins[motorNumber].pinIN1, LOW);
    digitalWrite(motorPins[motorNumber].pinIN2, HIGH);
  } else {
    digitalWrite(motorPins[motorNumber].pinIN1, LOW);
    digitalWrite(motorPins[motorNumber].pinIN2, LOW);
  }
}

void moveCar(int inputValue) {
  //Serial.printf("Got value as %s %d\n", inputValue.c_str(), inputValue.toInt());  Sang
  Serial.printf("Got value as %d\n", inputValue);
  //switch(inputValue.toInt())
  switch (inputValue) {

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

    case TURN_RIGHT:  //TURN_LEFT
      rotateMotor(FRONT_RIGHT_MOTOR, FORWARD);
      rotateMotor(BACK_RIGHT_MOTOR, FORWARD);
      rotateMotor(FRONT_LEFT_MOTOR, BACKWARD);
      rotateMotor(BACK_LEFT_MOTOR, BACKWARD);
      break;

    case TURN_LEFT:  //TURN_RIGHT
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

    default:
      rotateMotor(FRONT_RIGHT_MOTOR, STOP);
      rotateMotor(BACK_RIGHT_MOTOR, STOP);
      rotateMotor(FRONT_LEFT_MOTOR, STOP);
      rotateMotor(BACK_LEFT_MOTOR, STOP);
      break;
  }
}

void setup(void) {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);  //disable detector
                                              //pinMode(basePin, OUTPUT);
  for (int i = 0; i < motorPins.size(); i++) {
    pinMode(motorPins[i].pinIN1, OUTPUT);
    pinMode(motorPins[i].pinIN2, OUTPUT);
    rotateMotor(i, STOP);
  }
  pinMode(basePin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(MTL_PWM, OUTPUT);
  pinMode(MTR_PWM, OUTPUT);
  digitalWrite(basePin, HIGH);
  //digitalWrite(ledPin, HIGH);

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
  ledcWrite(0, 200);  // initial setup
}

void loop() {
  for (int i = 0; i < 2; i++) {
    moveCar(UP);
    delay(2000);
    moveCar(STOP);
    delay(1000);
    moveCar(DOWN);
    delay(2000);
    moveCar(STOP);
    delay(1000);
    Serial.printf("Loop time:  %d\n", i);
     }
    // Move DC motor forward with increasing speed
    moveCar(UP);
    while (dutyCycle <= 255) {
      ledcWrite(pwmChannel, dutyCycle);
      Serial.print("Forward with duty cycle: ");
      Serial.println(dutyCycle);
      dutyCycle = dutyCycle + 5;

      delay(500);
    }
    delay(1000);
    moveCar(STOP);
    Serial.printf("Stop\n");
    digitalWrite(ledPin, HIGH);
    while(1);

 
}
