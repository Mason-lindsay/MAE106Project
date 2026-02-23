#include <Arduino.h>
#include "Servos.h"
#include "Switch.h"
#include "Compass.h"
#include "Solenoid.h"

double orientation = 0;
double distance = 0;
double x = 0;
double y = 0;

// Replace with target coordinates
double targetX = 1;
double targetY = 1;
double target2X = 2;
double target2Y = 0;
double target3X = 0;
double target3Y = 2;
double target4X = 2;
double target4Y = 2;

bool targetReached = false;
bool endReached = false;

Compass compass;
Switch switchDevice;
Solenoid solenoidDevice;
Servo servo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting");
  ServoSetup();
  Serial.println("Servo Setup Complete");
  SwitchSetup();
  Serial.println("Switch Setup Complete");
  CompassSetup();
  Serial.println("Compass Setup Complete");
  SolenoidSetup();
  Serial.println("Solenoid Setup Complete");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (endReached) {
    Serial.println("All targets reached. Stopping.");
    servo.SetServo(90);
    solenoidDevice.off();
    while (true); // Stop the loop
  }

  targetReached = isTargetReached();
  if (!targetReached) {
    orientation = compass.read();
    distance = switchDevice.distanceTraveled();
    x += distance * cos(orientation * PI / 180);
    y += distance * sin(orientation * PI / 180);

    double distanceToTarget = targetDistance(x, y, targetX, targetY);
    double angleToTarget = targetAngle(x, y, targetX, targetY);
    double angleErr = angleError(angleToTarget, orientation);

    // Control logic for servo and solenoid based on errors
    if (abs(angleErr) > 10) { // If the angle error is significant
      double Kp = 0.5;
      double turn = Kp * angleErr;

      turn = constrain(turn, -30, 30);

      servo.SetServo(90 + turn);
    } else {
      SetServo(90); // Center the servo if we're mostly aligned
    }

    if (distanceToTarget > 0.1) { // If we're far from the target
      solenoidDevice.on(); // Activate solenoid to move forward
    } 
    else { 
      targetReached = true; // Target reached, set new target or stop moving
    }
  } else {
    setNewTarget(); // Move to the next target
  }
}


// put function definitions here:
void setNewTarget() {
  if (targetX == 1 && targetY == 1) {
    targetX = target2X;
    targetY = target2Y;
  } else if (targetX == target2X && targetY == target2Y) {
    targetX = target3X;
    targetY = target3Y;
  } else if (targetX == target3X && targetY == target3Y) {
    targetX = target4X;
    targetY = target4Y;
  }
  else {
    endReached = true; // All targets reached
  }
}

bool isTargetReached() {
  double tolerance = 0.05;  // meters
  if (targetDistance(x, y, targetX, targetY) < tolerance) {
    setNewTarget();
    return true;
  }
  return false;
}

double targetDistance(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

double targetAngle(double x1, double y1, double x2, double y2) {
  return atan2(y2 - y1, x2 - x1) * 180 / PI;
}

double angleError(double target, double current) {
  double error = target - current;
  // Normalize the error to the range [-180, 180]
  while (error > 180) error -= 360;
  while (error < -180) error += 360;
  return error;
}