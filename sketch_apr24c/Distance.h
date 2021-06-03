#ifndef Distance_h
#define Distance_h

#include "Joint.h"
#include "Arduino.h"

class Distance
{
  public:
    // The Joystick constructor.
    Distance(int trigPin, int echoPin);

    void setPinMode();

    void listen(Joint joints[]);

  private:

    int _trigPin;
    
    int _echoPin;
    
    int _offset;

    int _isClosed;
    
    int _isOpen;
    
    int _triggerDist;

    long _duration;

    int _distance;

};

#endif
