#include "Arduino.h"
#include "Joystick.h"
#include "Joint.h"

// The Joystick constructor.
Joystick::Joystick(int VRx, int VRy, int SW)
{
  _VRx = VRx;
  _VRy = VRy;
  _SW = SW;
  
  _x_min = -20;
  _x_max = 20;
  _y_min = -20;
  _y_max = 20;

  _analog_min = 0;
  _analog_max = 1023;
}

void Joystick::setPinMode()
{
  pinMode(_VRx, INPUT);
  pinMode(_VRy, INPUT);
  pinMode(_SW, INPUT_PULLUP); 
}

void Joystick::listen(Joint joints[])
{
  int xPosition = analogRead(_VRx);
  int yPosition = analogRead(_VRy);
  int SW_state = digitalRead(_SW);
  
  int x = map(xPosition, _analog_min, _analog_max, _x_min, _x_max);
  int y = map(yPosition, _analog_min, _analog_max, _y_min, _y_max);
  
  if (SW_state == 0) {
    int degreeA = joints[0].getRotation();
    int nextA = (degreeA + y);
    joints[0].smoothRotation(nextA);

    int degreeB = joints[1].getRotation();
    int nextB = (degreeB + x);
    joints[1].smoothRotation(nextB);

    int degreeC = joints[2].getRotation();
    int nextC = (degreeC + (-x));
    joints[2].smoothRotation(nextC);

    int degreeD = joints[3].getRotation();
    int nextD = (degreeD + (-x));
    joints[3].smoothRotation(nextD);
  } 
}
