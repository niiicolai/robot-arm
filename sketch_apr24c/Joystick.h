#ifndef Joystick_h
#define Joystick_h

#include "Joint.h"
#include "Arduino.h"

class Joystick
{
  public:
    // The Joystick constructor.
    Joystick(int VRx, int VRy, int SW);

    void setPinMode();

    void listen(Joint joints[]);

  private:

    int _VRx;
    
    int _VRy;
    
    int _SW;

    int _x_min;
    
    int _x_max;
    
    int _y_min;

    int _y_max;

    int _analog_min;

    int _analog_max;

};

#endif
