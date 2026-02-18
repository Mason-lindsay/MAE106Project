#include "Servos.h"
#include <Arduino.h>

Servo servo;
int servoMax = 180;
int servoMin = 0;
double servoAngle = 0;

/// @brief Sets the servo to the specified angle, ensuring it stays within defined limits
/// @param angle (int): Desired angle to set the servo to
void SetServo(int angle) {
    if (angle > servoMax) {
        angle = servoMax;
    } else if (angle < servoMin) {
        angle = servoMin;
    }
    servo.write(angle); // Set the servo to the specified angle
    servoAngle = angle;
}

void ServoSetup() {
    servo.attach(SERV_IN); // Attach the servo to the defined pin
    servo.write(90); // Set initial position to 90 degrees
}

/// @brief Example loop to sweep the servo from 0 to 180 degrees and back. Used for testing and demonstration purposes.
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