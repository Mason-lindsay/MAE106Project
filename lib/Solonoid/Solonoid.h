#ifndef Solonoid_H
#define Solonoid_H

#include <Arduino.h>

#define SOL_IN 8 // Replace with the actual pin number

class Solonoid {
public:
    void attach(int pin);
    void write(int value);
    
private:
    int pin_;
};

void SolonoidSetup();
void SolonoidLoop();
#endif