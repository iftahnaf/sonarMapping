/* 
 * Arduino Learning Board Project - HC-SR04 Ultrasonic Sensor Example
 *
 * Please visit http://www.ArduinoLearningBoard.com for more information
 *
 * Last modified August 2016 by Jeff Shapiro <Jeff@ArduinoLearningBoard.com>
 */

/*
VCC  -> 5V
Trig -> D2
Echo -> D4
GND  -> GND
*/
#include <Arduino.h>
#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
#include "readSonar.h"
#define trigPin 2
#define echoPin 4

ros::NodeHandle  nh;

sensor_msgs::Range range_msg;
ros::Publisher pub_range( "/ultrasound", &range_msg);
sonar ultrasonic;


long duration;     // Duration used to calculate distance
float distance;

char frameid[] = "/ultrasound";

void setup()
{
  nh.initNode();
  nh.advertise(pub_range);
  
  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 0.1;  // fake
  range_msg.min_range = 0.0;
  range_msg.max_range = 6.47;
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

long range_time;

void loop()
{
  //publish the adc value every 50 milliseconds
  //since it takes that long for the sensor to stablize

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Call pulseIn function to wait for High pulse
  // result will be time in microseconds until pulse is detected
  duration = pulseIn(echoPin, HIGH);

  if (duration < 100000)
  {
    distance = ultrasonic.microSecondsToCentimeters(duration);
    range_msg.range = distance;
    range_msg.header.stamp = nh.now();
    pub_range.publish(&range_msg);
  }
  delay(100); 

  nh.spinOnce();
}
