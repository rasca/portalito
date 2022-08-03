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

class Align {
    public:
    void setup();
    void tick();
};

class Sonar {
    public:
    double speed = 0.3;
    double angle = 0;

    void setup();
    void tick();

    private:
    unsigned long _lastTimestamp = 0;

};

class CircularWave {
    public:
    double angle = 0;
    double previousAngle = 360;

    float maxAmplitude = 5;
    float speed = 0.01;
    float angleSpeed = 0.1;

    void setup();
    void tick();

    private:
    unsigned long _lastTimestamp = 0;
    // TODO: make it work for multiple segments
    bool circularWave = true;
    float amplitude = 0;

};

#endif