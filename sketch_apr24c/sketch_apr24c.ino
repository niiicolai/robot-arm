
#include "Joint.h"
#include <Regexp.h>

// Joint(DEFAULT_DEGREE, MIN_DEGREE, MAX_DEGREE, SMOOTH_ROTATION_DELAY, TITLE)
Joint joints[] = {
  Joint(100, 30, 150, 20, "A"),
  Joint(82, 30, 150, 20, "B"),
  Joint(75, 40, 180, 20, "C"),
  Joint(80, 40, 180, 20, "D"),
  Joint(90, 30, 180, 20, "E")
};

String write_command = "WRITE";
String read_command = "READ";
String reset_command = "RESET";
String random_command = "RANDOM";

int max_joints = 5;

void setup() {
  joints[0].attach(8);
  joints[1].attach(9);
  joints[2].attach(10);
  joints[3].attach(11);
  joints[4].attach(12);
  
  // Init the serial monitor
  Serial.begin(9600);

  // Wait until serial monitor is started
  while (!Serial) {};

  delay(20);
  Serial.println("");
  Serial.println("STARTING ARM...");
  Serial.println("==> RESETTING JOINTS ROTATION");

  // Loop all joints
  for (int i = 0; i < max_joints; i++) {
    Serial.println("==> RESETTING JOINT: " + joints[i].getTitle());
    // Set their rotation to default
    joints[i].defaultRotation();
  }

  Serial.println("==> READY");
}

void loop() {
  String message = Serial.readString();
  if (message != "")
  {
    Serial.println("");
    Serial.println("READING SERIAL COMMAND...");
    Serial.println("==> COMMAND: " + message);
    command(message);
  }
}

void command(String cmd)
{
  // Ensure to allow lowercase commands
  cmd.toUpperCase();

  // Used to match the cmd
  MatchState ms;
  // The string we want to match
  // in this case the String command
  ms.Target (cmd.c_str());


  // Check if the reset command should be executed
  if (ms.Match (reset_command.c_str(), 0) == REGEXP_MATCHED) {
    Serial.println("==> RESETTING JOINTS ROTATION");
    
    // Loop all joints
    for (int i = 0; i < max_joints; i++) {
      Serial.println("==> RESETTING JOINT: " + joints[i].getTitle());
      // Set their rotation to default
      joints[i].defaultRotation();
    }

    Serial.println("==> READY");
  }

  // Check if the random command should be executed
  else if (ms.Match (random_command.c_str(), 0) == REGEXP_MATCHED) {
    Serial.println("==> ROTATING JOINTS RANDOM");
    
    // Loop all joints
    for (int i = 0; i < max_joints; i++) {
      Serial.println("==> ROTATING JOINT: " + joints[i].getTitle());
      // Set their rotation to default
      joints[i].randomRotation();
    }

    Serial.println("==> READY");
  }

  // Else check if the command was meant for one of
  // the joints instead
  else
  {
    bool found_execution = false;
    // Loop all joints
    for (int i = 0; i < max_joints; i++) {
      // Check if the joint's title match anything
      // in the given command
      if (joints[i].matchTitle(cmd)) {
        Serial.println("==> FOUND JOINT: " + joints[i].getTitle());
        
        // If it does, we check to see if it was a write command
        if (ms.Match ("WRITE", 0) == REGEXP_MATCHED) {

          // parse the degree expected to find within
          // the command string
          int degree = parseDegree(cmd);
          Serial.println("==> WRITING DEGREES: ");
          Serial.println(degree);
          // Rotate the joint smoothly with a given degree
          joints[i].smoothRotation(degree);

          
          found_execution = true;
        }

        // Or if it was a read command
        else if (ms.Match ("READ", 0) == REGEXP_MATCHED)
        {
          // Print the joint's current state to serial
          joints[i].printStateToSerial();

          found_execution = true;
        }
        
        break;
      }
    }

    if (!found_execution) {
      Serial.println("==> FOUND NO VALID COMMAND");
    }

    Serial.println("==> READY");
  }
}

int parseDegree(String s)
{
  // Split command at n index
  String sub = s.substring(7);
  // Parse integers from command
  int degree = sub.toInt();
  return degree;
}
