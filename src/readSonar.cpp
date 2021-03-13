#include <Arduino.h>
#include <Ultrasonic.h>
#include "readSonar.h"

float sonar::microSecondsToCentimeters(long microseconds)
{
  // Sound travels at 1125 feet per second
  // or 29.386 microseconds per centimeter
  // This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  return microseconds / 29.387 / 2.0;
}

long sonar::timeTravel(const int echoPin, const int trigPin){
  long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration;
}