#include "Compass.h"
#include <math.h>

bool Compass::begin() {
    Wire.begin();
    if (!mag.begin_I2C()) {
        return false;
    }
    return true;
}

float Compass::read() {
    sensors_event_t event;
    mag.getEvent(&event);
    float heading = atan2(event.magnetic.y, event.magnetic.x) * 180 / PI;
    if (heading < 0) heading += 360;
    return heading;
}