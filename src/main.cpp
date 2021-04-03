/*
Ultrasonic:
VCC  -> 5V
Trig -> D2
Echo -> D4
GND  -> GND
Servo:
PWM -> D9
*/
#include <Arduino.h>
#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
#include "readSonar.h"
#include <Servo.h>
#include <std_msgs/UInt16.h>

#define trigPin 2
#define echoPin 4
#define servoPin 9
#define servoPower 13

ros::NodeHandle  nh;

sensor_msgs::Range range_msg;
ros::Publisher pub_range( "/ultrasound", &range_msg);
sonar ultrasonic;
std_msgs::UInt16 servoPos;
ros::Publisher pub_pos("/servo", &servoPos);
Servo myservo;

long duration;
float distance;
char frameid[] = "/ultrasound";
int pos = 60;
int flag = 0;

void setup()
{
  nh.initNode();
  nh.advertise(pub_range);
  nh.advertise(pub_pos);
  
  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 60.0;  // fake
  range_msg.min_range = 0.0;
  range_msg.max_range = 1200.00;
    
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(servoPower,OUTPUT);
  digitalWrite(servoPower, HIGH);

  myservo.attach(servoPin);
}

void loop()
{
  myservo.write(pos);

  duration = ultrasonic.timeTravel(echoPin, trigPin);

  servoPos.data = pos;
  pub_pos.publish(&servoPos);

  if (duration < 100000)
  {
    distance = ultrasonic.microSecondsToCentimeters(duration);
    range_msg.range = distance;
    range_msg.header.stamp = nh.now();
    pub_range.publish(&range_msg);
  }

  delay(10); 

  if ((pos <= 135) && flag == 0){
    pos=pos+2;
  }
  else{
    flag =1;
    pos=pos-2;
  }
  if (pos < 60){
    flag = 0;
    pos = 60;
  }

  nh.spinOnce();
}
