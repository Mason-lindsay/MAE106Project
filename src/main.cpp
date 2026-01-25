#include <Arduino.h>
#include "Servo1.h"


// put function declarations here:


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting");
  ServoSetup();
  Serial.println("Servo Setup Complete");
}

void loop() {
  // put your main code here, to run repeatedly:
  ServoLoop(); // Call the servo loop function
}

// put function definitions here:
