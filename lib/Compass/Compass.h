#ifndef Compass_H
#define Compass_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_LIS3MDL.h>

class Compass {
private:
    Adafruit_LIS3MDL mag;

public:
    bool begin();           // Initialize sensor
    float read();           // Return heading in degrees
};

#endif