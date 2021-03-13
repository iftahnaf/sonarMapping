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
#include <std_msgs/String.h>
#define trigPin 2
#define echoPin 4

ros::NodeHandle  nh;

sensor_msgs::Range range_msg;
ros::Publisher pub_range( "/ultrasound", &range_msg);
sonar ultrasonic;
std_msgs::String str_msg;
ros::Publisher chatter("/test", &str_msg);


long duration;
float distance;
char hello[13] = "hello world!";

char frameid[] = "/ultrasound";

void setup()
{
  nh.initNode();
  nh.advertise(pub_range);
  nh.advertise(chatter);
  
  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 0.1;  // fake
  range_msg.min_range = 0.0;
  range_msg.max_range = 1200.00;
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  duration = ultrasonic.timeTravel(echoPin, trigPin);

  str_msg.data = hello;
  chatter.publish( &str_msg );

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
