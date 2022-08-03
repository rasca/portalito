#ifndef LEDS_H_INCLUDED
#define LEDS_H_INCLUDED

///// LEDS /////

#include <FastLED.h>
#include <array>

#define NUM_LEDS 500
#define NUM_SEGMENTS 1

#define NUM_COL_LEDS 35
#define NUM_EXTRA_BOTTOM_LEDS 30
#define NUM_COLS_PER_SEGMENT (NUM_LEDS / (NUM_COL_LEDS * 2 + NUM_EXTRA_BOTTOM_LEDS) * 2)
#define NUM_COLS (NUM_COLS_PER_SEGMENT * NUM_SEGMENTS)

class Leds {
    public:
    void setup();
    void tick();

    private:
    byte hue = 0;
};

class Sonar {
    public:
    double speed = 0.03;
    double angle = 0;
    double previousAngle = 360;

    float circularWaveMaxAmplitude = 5;
    float circularWaveSpeed = 0.001;

    void setup();
    void tick();

    private:
    unsigned long _lastTimestamp = 0;
    // TODO: make it work for multiple segments
    bool circularWave = true;
    float circularWaveAmplitude = 0;

};

#endif