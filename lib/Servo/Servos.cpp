#include "Servos.h"
#include <Arduino.h>

Servo servo;
int midpoint = 90; // Define midpoint angle

void ServoSetup() {
    servo.attach(SERV_IN); // Attach the servo to the defined pin
    servo.write(midpoint); // Set initial position to 90 degrees
}

void ServoLoop() {
    // Example loop to sweep the servo from 0 to 180 degrees and back
    for (int angle = 0; angle <= 180; angle += 1) {
        servo.write(angle);
        delay(15); // Wait for the servo to reach the position
    }
    for (int angle = 180; angle >= 0; angle -= 1) {
        servo.write(angle);
        delay(15); // Wait for the servo to reach the position
    }
}