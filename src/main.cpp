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

double Kp = 0.6;
double Ki = 0.01;
double Kd = 0.05;

double integral = 0;
double prevError = 0;

unsigned long prevTime = 0;

// Replace with target coordinates
// Reference frame changes with each target, so we reset x and y to 0 at each new target
double targetX = 0;
double targetY = 1;
double target2X = 5;
double target2Y = 0;
double target3X = 5;
double target3Y = 0;
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
    prevTime = millis();

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
    prevTime = millis();
}

void loop() {  
  // Activate solenoid to start moving 
  solenoidDevice.on(); 

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
    double angleToTarget = targetAngle(x, y, targetX, targetY); 
    double angleErr = angleError(angleToTarget, orientation); 
        
    // Control logic for servo and solenoid based on errors 
    unsigned long currentTime = millis(); 
    double dt = (currentTime - prevTime) / 1000.0; // seconds 
        
    if (dt <= 0) dt = 0.001; 
        
    double error = angleErr; 
        
    if (abs(error) < 5) { 
      integral = 0; 
      SetServo(90); 
    } 
    else { 
      integral += error * dt; 
      integral = constrain(integral, -50, 50); 
      double derivative = (error - prevError) / dt; 
      double turn = Kp * error + Ki * integral + Kd * derivative; 
      turn = constrain(turn, -30, 30); SetServo(90 - turn); 
    } 
  } 
  else { 
    setNewTarget(); 
  } 
}

/// @brief Initializes the compass sensor and checks if it was successful
void CompassSetup() {
    if (!compass.begin()) {
        Serial.println("Failed to initialize compass!");
        while (1); // Stop the program if the sensor isn't found
    }
}

/// @brief Initializes the solenoid and attaches it to the specified pin
void SolenoidSetup() {
    solenoidDevice.attach(SOL_PIN);
}

/// @brief Initializes the switch and attaches it to the specified pin
void SwitchSetup() {
    switchDevice.attach(SWITCH_IN);
}

/// @brief Sets the next target coordinates and resets the position and PID state for the new target
void setNewTarget() {

  if (abs(targetX - 1.0) < 1e-6 && abs(targetY - 1.0) < 1e-6) {
    targetX = target2X;
    targetY = target2Y;
    x = 0;
    y = 0;

    integral = 0;
    prevError = 0;
    prevTime = millis();

  } else if (abs(targetX - target2X) < 1e-6 && abs(targetY - target2Y) < 1e-6) {
    targetX = target3X;
    targetY = target3Y;
    x = 0;
    y = 0;

    integral = 0;
    prevError = 0;
    prevTime = millis();

  } else if (targetX == target3X && targetY == target3Y) {
    targetX = target4X;
    targetY = target4Y;
    x = 0;
    y = 0;

    integral = 0;
    prevError = 0;
    prevTime = millis();

  }
  else {
    endReached = true; // All targets reached
  }
}

/// @brief Checks if the current position is within a certain tolerance of the target coordinates
/// @return true if the target is reached, false otherwise
bool isTargetReached() {
  double tolerance = 0.05;  // meters
  if (targetDistance(x, y, targetX, targetY) < tolerance) {
    return true;
  }
  return false;
}

/// @brief Calculates current distance to target
/// @param x1 
/// @param y1 
/// @param x2 
/// @param y2 
/// @return distance to target
double targetDistance(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

/// @brief calculats current angle to target in degrees, where 0 degrees is directly to the right, 90 degrees is directly up
/// @param x1 
/// @param y1 
/// @param x2 
/// @param y2 
/// @return angle to target in degrees
double targetAngle(double x1, double y1, double x2, double y2) {
  return atan2(y2 - y1, x2 - x1) * 180 / PI;
}

/// @brief calculates the angle error between the target angle and current orientation
/// @param target 
/// @param current 
/// @return error in degrees
double angleError(double target, double current) {
  double error = target - current;
  // Normalize the error to the range [-180, 180]
  while (error > 180) error -= 360;
  while (error < -180) error += 360;
  return error;
}