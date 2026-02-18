#include <Arduino.h>
#include "Servos.h"
#include "Switch.h"
#include "Compass.h"
#include "Solenoid.h"

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
  
}

// put function definitions here:
double angleError(double target, double current) {
  double error = target - current;
  // Normalize the error to the range [-180, 180]
  while (error > 180) error -= 360;
  while (error < -180) error += 360;
  return error;
}