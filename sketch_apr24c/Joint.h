#ifndef Joint_h
#define Joint_h

#include "Arduino.h"
#include <Servo.h>

class Joint
{
  public:
    // The Joint constructor.
    Joint(int default_rotation_degree, int min_rotation_degree,
          int max_rotation_degree, int smooth_rotation_delay, String title);

    // Rotate the joint smoothly over time
    // to a given rotation in degrees within
    // the min and max rotation
    void smoothRotation(int degree);

    // Rotate the joint instant to a given
    // rotation in degrees within the
    // min and max rotation
    void instantRotation(int degree);

    // Rotate the joint to a random rotation
    // within min and max rotation
    void randomRotation();

    // Rotate the joint to its default rotation
    void defaultRotation();

    // Return true if the given string's content
    // is equal to the Joint's title
    bool matchTitle(String title);

    // Writes information about the joint to the
    // serial connection
    void printStateToSerial();

    // Returns the joint's title
    String getTitle();

    void attach(int pin);

  private:

    // A specific degree where the Joint is considered
    // to be at its default position.
    int _default_rotation_degree;

    // The min rotation degree
    int _min_rotation_degree;

    // The max rotation degree
    int _max_rotation_degree;

    // The amount of delay in seconds,
    // the smooth rotation method use to 'simulate'
    // smooth rotation
    int _smooth_rotation_delay;

    // The title of the Joint instance
    String _title;

    // The actual servo object used
    // to attach, read, and write from and to a servo motor
    Servo _servo;
};

#endif
