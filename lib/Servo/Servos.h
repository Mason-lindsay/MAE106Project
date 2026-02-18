#ifndef SERVO1_H
#define SERVO1_H

#include <Servo.h>
#include <Arduino.h>

#define SERV_IN 9 // Replace with the actual pin number

    void ServoSetup();
    void ServoLoop();
    void SetServo(int angle);

#endif // SERVO1_H
