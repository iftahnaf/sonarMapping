#include <Arduino.h>
#include "readSonar.h"
#include <ros.h>
#include <sensor_msgs/Range.h>

double dist;
const int trigPin = 9;
const int echoPin = 4;

ros::NodeHandle nh;
sensor_msgs::Range range_msg;
sonar HC_SR04;
ros::Publisher pub_range("/ultrasound", &range_msg);

void setup() {
  // put your setup code here, to run once:
  HC_SR04.sonarSetup(trigPin, echoPin);
  nh.initNode();
  nh.advertise(pub_range);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  dist = HC_SR04.read(trigPin, echoPin);
}