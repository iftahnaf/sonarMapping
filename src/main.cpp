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

ros::NodeHandle nh;

sensor_msgs::Range range_msg;
ros::Publisher pub_range("/ultrasound", &range_msg);
sonar ultrasonic;
std_msgs::UInt16 servoPos;
ros::Publisher pub_pos("/servo", &servoPos);
Servo myservo;

char frameid[] = "/ultrasound";
int pos = 60;
int flag = 0;
int minAngle = 35;
int maxAngle = 135;

void controlServo(int &pos, int &flag, int minAngle, int maxAngle, Servo &myservo, std_msgs::UInt16 &servoPos, ros::Publisher &pub_pos)
{
  if ((pos <= maxAngle) && flag == 0)
  {
    pos = pos + 2;
  }
  else
  {
    flag = 1;
    pos = pos - 2;
  }
  if (pos < minAngle)
  {
    flag = 0;
    pos = minAngle;
  }
  myservo.write(pos);
  servoPos.data = pos;
  pub_pos.publish(&servoPos);
}

void publishMeasuredDistance(sensor_msgs::Range &range_msg, ros::Publisher &pub_range)
{
  long duration;
  float distance;
  duration = ultrasonic.timeTravel(echoPin, trigPin);
  distance = ultrasonic.microSecondsToCentimeters(duration);
  range_msg.range = distance;
  range_msg.header.stamp = nh.now();
  pub_range.publish(&range_msg);
}

void setupRangeMessage(sensor_msgs::Range &range_msg)
{
  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id = frameid;
  range_msg.field_of_view = 75.0;
  range_msg.min_range = 0.0;
  range_msg.max_range = 1200.00;
}

void setup()
{
  nh.initNode();
  nh.advertise(pub_range);
  nh.advertise(pub_pos);

  setupRangeMessage(range_msg);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myservo.attach(servoPin);
}

void loop()
{
  controlServo(pos, flag, minAngle, maxAngle, myservo, servoPos, pub_pos);
  publishMeasuredDistance(range_msg, pub_range);
  delay(2);
  nh.spinOnce();
}

