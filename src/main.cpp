#include <Arduino.h>
#include "readSonar.h"
#include <Servo.h>
#include <ros.h>
#include <sensor_msgs/Range.h>
#include <ros/time.h>

#define MAX_ANGLE 60

double dist;
int pos;
const int trigPin = 9;
const int echoPin = 4;
const int servoPin = 10;

sonar HC_SR04;
Servo rotServo;

void setup() {
  // setup the ultrasonic sensor
  HC_SR04.sonarSetup(trigPin, echoPin);
  // setup the servo
  rotServo.attach(servoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(pos = 0; pos<=MAX_ANGLE; pos++){
    dist = HC_SR04.read(trigPin, echoPin);
    rotServo.write(pos);
    Serial.print("\t Servo Position [deg]: ");
    Serial.print(pos);
  }
  for(pos = MAX_ANGLE; pos >=0; pos--){
    dist = HC_SR04.read(trigPin, echoPin);
    rotServo.write(pos);
    Serial.print("\t Servo Position [deg]: ");
    Serial.print(pos);
  }
}