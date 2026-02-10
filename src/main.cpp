#include <Arduino.h>
#include "Servos.h"
#include "Switch.h"
#include "Compass.h"
#include "Solonoid.h"


// put function declarations here:


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
  SolonoidSetup();
  Serial.println("Solonoid Setup Complete");
}

void loop() {
  // put your main code here, to run repeatedly:
  ServoLoop(); // Call the servo loop function
  SwitchLoop(); // Call the switch loop function
  CompassLoop(); // Call the compass loop function
  SolonoidLoop(); // Call the solonoid loop function
}

// put function definitions here:
