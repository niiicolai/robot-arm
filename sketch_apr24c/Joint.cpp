#include "Arduino.h"
#include "Joint.h"
#include <Regexp.h>

// The Joint constructor.
Joint::Joint(int default_rotation_degree, int min_rotation_degree, 
      int max_rotation_degree, int smooth_rotation_delay, String title)
{
  _min_rotation_degree = min_rotation_degree;
  _max_rotation_degree = max_rotation_degree;
  _default_rotation_degree = constrain(default_rotation_degree, 
    _min_rotation_degree, _max_rotation_degree);
    
  _smooth_rotation_delay = smooth_rotation_delay;
  _title = title;
}

void Joint::attach(int pin)
{
  _servo.attach(pin);
}

// Returns the joint's title
String Joint::getTitle()
{
  return _title;
}

// Returns the joint's rotation
int Joint::getRotation()
{
  return _servo.read();
}

// Return true if the given string's content
// is matching the Joint's title somewhere
bool Joint::matchTitle(String title)
{
  // Split command at n index
  String sub = title.substring(0, 1);
  return _title.equals(sub);
}

// Rotate the joint instant to a given
// rotation in degrees within the
// min and max rotation
void Joint::instantRotation(int degree)
{
  // Ensure the given degree doesn't exceed min and max.
  degree = constrain(degree, _min_rotation_degree, _max_rotation_degree);
  // Signal the servo to rotate to the given degree
  _servo.write(degree);
}

// Rotate the joint to its default rotation
void Joint::defaultRotation()
{
  // Rotate to the default degree using smooth rotation
  smoothRotation(_default_rotation_degree);
}

// Rotate the joint to a random rotation
// within min and max rotation
void Joint::randomRotation()
{
  // Get a random degree within the min and max
  int random_degree = random(_min_rotation_degree, _max_rotation_degree);
  // Rotate to the random degree using smooth rotation
  smoothRotation(random_degree);
}

// Rotate the joint smoothly over time
// to a given rotation in degrees within
// the min and max rotation
void Joint::smoothRotation(int degree)
{
  // Ensure the given degree doesn't exceed min and max.
  degree = constrain(degree, _min_rotation_degree, _max_rotation_degree);
  
  int current_servo_degree = _servo.read();
  
  // INCREASE DEGREE CONDITION
  if (degree > current_servo_degree) {
      // Loop until the current degree is greater than the given degree
      for (int i = current_servo_degree; i < degree; i++)
      {
        // Add delay to ensure the loop doesn't run with
        // the same rate as the Arduino's framerate.
        delay(_smooth_rotation_delay);

        // Signal the servo to rotate to the new current degree
        _servo.write(i);
      }
  }
  // DECREASE DEGREE CONDITION
  else if (degree < current_servo_degree) {
    // Loop until the current degree is less than the given degree
      for (int i = current_servo_degree; i > degree; i--)
      {
        // Add delay to ensure the loop doesn't run with
        // the same rate as the Arduino's framerate.
        delay(_smooth_rotation_delay);

        // Signal the servo to rotate to the new current degree
        _servo.write(i);
      }
  }
}

// Writes information about the joint to the
// serial connection
void Joint::printStateToSerial()
{
  Serial.println("==> TITLE: ");
  Serial.println(_title);

  Serial.println("==> SMOOTH ROTATION DELAY: ");
  Serial.println(_smooth_rotation_delay);

  Serial.println("==> DEFAULT DEGREE: ");
  Serial.println(_default_rotation_degree);

  Serial.println("==> MIN DEGREE: ");
  Serial.println(_min_rotation_degree);

  Serial.println("==> MAX DEGREE: ");
  Serial.println(_max_rotation_degree);
        
  Serial.println("==> CURRENT DEGREE: ");
  Serial.println(_servo.read());
}
