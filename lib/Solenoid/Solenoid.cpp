#include "Solenoid.h"

void Solenoid::attach(int pin) {
    pin_ = pin;
    pinMode(pin_, OUTPUT);
    off();  // start OFF for safety
}

void Solenoid::on() {
    digitalWrite(pin_, HIGH);
    state_ = true;
}

void Solenoid::off() {
    digitalWrite(pin_, LOW);
    state_ = false;
}

void Solenoid::toggle() {
    if (state_) {
        off();
        delay(900);
    } else {
        on();
        delay(700); // Keep the solenoid on for 700 ms
    }
}

bool Solenoid::isOn() {
    return state_;
}
