#include <Arduino.h>
#include <Ultrasonic.h>
#include "readSonar.h"


void sonar::sonarSetup(const int trigPin, const int echoPin){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(9600);
}

int sonar::read(const int trigPin, const int echoPin){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duritation = pulseIn(echoPin, HIGH);
    distance = duritation*0.034/2;
    Serial.print("\nDistance [cm]: ");
    Serial.print(distance);
    Serial.print("\tDuratation: ");
    Serial.print(duritation);

    return distance;
}

void sonar::hazard(int distance, const int ledPin, const int minDist){
    if (distance < minDist){
        digitalWrite(ledPin, HIGH);
    }
    else{
        digitalWrite(ledPin, LOW);
    }
}