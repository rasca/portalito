#ifndef LEDS_H_INCLUDED
#define LEDS_H_INCLUDED

///// LEDS /////

#include <FastLED.h>
#include <array>

#define NUM_LEDS 50
#define NUM_SEGMENTS 5

#define NUM_COL_LEDS 23
#define NUM_EXTRA_BOTTOM_LEDS 4
#define NUM_COLS_PER_SEGMENT (NUM_LEDS / (NUM_COL_LEDS * 2 + NUM_EXTRA_BOTTOM_LEDS) * 2)

class Leds {
    public:
    void setup();
    void tick();

    private:
    byte hue = 0;
};

class Sonar {
    public:
    double speed = 0.000000001;
    double angle = 0;

    void setup();
    void tick();

    private:
    unsigned long _lastTimestamp = 0;

};

#endif