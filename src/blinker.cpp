#include "blinker.hpp"

// Constructor
Blinker::Blinker(uint32_t dur) : 
    dur(dur),
    on(false)
{}

// Constructor
Blinker::Blinker() : 
    dur(1000000),
    on(false)
{}

void Blinker::init() {
    
}

// Blink the LED
bool Blinker::blink() {
    if(frame > dur)
    {
        on = !on;
        frame = 0;
    }
    frame++;
    return on;        // Turn LED on
}
