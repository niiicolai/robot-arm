#include "Arduino.h"
#include "Distance.h"
#include "Joint.h"

// The Distance constructor.
Distance::Distance(int trigPin, int echoPin)
{
  _trigPin = trigPin;
  _echoPin = echoPin;
  
  _offset = 5;
  _isClosed = 80;
  _isOpen = 20;

  _triggerDist = 10;
}

void Distance::setPinMode()
{
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);
}

void Distance::listen(Joint joints[])
{
  // Ultrasonic Sensor
  // Clears the trigPin
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  _duration = pulseIn(_echoPin, HIGH);
  
  // Calculating the distance
  _distance = (_duration * (0.034/2));
  
  if (_distance < _triggerDist) {
    int degreeE = joints[4].getRotation();
    
    Serial.println("degreeE: ");
    Serial.print(degreeE);
    
    if (degreeE < _isClosed) {
      joints[4].smoothRotation(_isClosed+_offset);
      Serial.println("isClosed");
    }
    else
    {
      joints[4].smoothRotation(_isOpen);
      Serial.println("isOpen");
    }
  }
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(_distance);
}
