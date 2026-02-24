#include <Arduino.h>
#include <Wire.h>                
#include "Servos.h"
#include "Switch.h"
#include "Compass.h"
#include "Solenoid.h"

double orientation = 0;
double distance = 0;
double x = 0;
double y = 0;

// Replace with target coordinates
// Reference frame changes with each target, so we reset x and y to 0 at each new target
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

void SwitchSetup();
void CompassSetup();
void SolenoidSetup();
void setNewTarget();
bool isTargetReached();
double targetDistance(double x1, double y1, double x2, double y2);
double targetAngle(double x1, double y1, double x2, double y2);
double angleError(double target, double current);

void setup() {
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

    delay(15000);
}

void loop() {
  //Check if all targets have been reached
  if (endReached) {
    Serial.println("All targets reached. Stopping.");
    SetServo(90);
    solenoidDevice.off();
    while (true); // Stop the loop
  }

  // Main control loop
  targetReached = isTargetReached();

  // Read sensor data and update position
  if (!targetReached) {
    orientation = compass.read();
    distance = switchDevice.distanceTraveled();
    x += distance * cos(orientation * PI / 180);
    y += distance * sin(orientation * PI / 180);

    // Calculate distance and angle to target
    double distanceToTarget = targetDistance(x, y, targetX, targetY);
    double angleToTarget = targetAngle(x, y, targetX, targetY);
    double angleErr = angleError(angleToTarget, orientation);

    // Control logic for servo and solenoid based on errors
    if (abs(angleErr) > 10) { // If the angle error is significant
      double Kp = 0.5;
      double turn = Kp * angleErr;

      turn = constrain(turn, -30, 30);

      SetServo(90 + turn);
    } else {
      SetServo(90); // Center the servo if we're mostly aligned
    }

    // Control solenoid based on distance to target
    if (distanceToTarget > 0.1) { // If we're far from the target
      solenoidDevice.toggle(); // Activate solenoid to move forward
    } 
    else { 
      targetReached = true; // Target reached, set new target or stop moving
    }
  } else {
    setNewTarget(); // Move to the next target
  }
}


// put function definitions here:
void CompassSetup() {
    if (!compass.begin()) {
        Serial.println("Failed to initialize compass!");
        while (1); // Stop the program if the sensor isn't found
    }
}

void SolenoidSetup() {
    solenoidDevice.attach(SOL_PIN);
}

void SwitchSetup() {
    switchDevice.attach(SWITCH_IN);
}

void setNewTarget() {
  if (abs(targetX - 1.0) < 1e-6 && abs(targetY - 1.0) < 1e-6) {
    targetX = target2X;
    targetY = target2Y;
    x = 0;
    y = 0;
  } else if (abs(targetX - target2X) < 1e-6 && abs(targetY - target2Y) < 1e-6) {
    targetX = target3X;
    targetY = target3Y;
    x = 0;
    y = 0;
  } else if (targetX == target3X && targetY == target3Y) {
    targetX = target4X;
    targetY = target4Y;
    x = 0;
    y = 0;
  }
  else {
    endReached = true; // All targets reached
  }
}

bool isTargetReached() {
  double tolerance = 0.05;  // meters
  if (targetDistance(x, y, targetX, targetY) < tolerance) {
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