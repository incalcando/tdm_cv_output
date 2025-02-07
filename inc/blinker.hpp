#ifndef BLINKER_H
#define BLINKER_H

#include "pico/stdlib.h"

class Blinker {
private:
    uint32_t frame;  
    uint32_t dur;
    bool on;

public:
    // Constructor
    Blinker(uint32_t dur);
    Blinker();

    // Initialize the GPIO pin
    void init();

    void setDur(uint dur) { this->dur = dur; };

    // Blink the LED (on, wait, off, wait)
    bool blink();
};

#endif // BLINKER_H
