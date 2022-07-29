#ifndef LEDS_H_INCLUDED
#define LEDS_H_INCLUDED

///// LEDS /////

#include <FastLED.h>
#include <array>

#define NUM_LEDS 500
#define NUM_SEGMENTS 5

std::array<std::array<CRGB, NUM_LEDS>, NUM_SEGMENTS> segments;

class Leds {
    public:
    void setup()
    {
        // LEDS
        // 16 17 5 18 19
        FastLED.addLeds<WS2812, GPIO_NUM_16>(segments[0].data(), NUM_LEDS);
        FastLED.addLeds<WS2812, GPIO_NUM_17>(segments[0].data(), NUM_LEDS);
        FastLED.addLeds<WS2812, GPIO_NUM_5>(segments[0].data(), NUM_LEDS);
        FastLED.addLeds<WS2812, GPIO_NUM_18>(segments[0].data(), NUM_LEDS);
        FastLED.addLeds<WS2812, GPIO_NUM_19>(segments[0].data(), NUM_LEDS);
        FastLED.setBrightness(204);
    }

    void tick()
    {
        FastLED.clear();
        for (int i = 0; i < NUM_SEGMENTS; i++)
        {
            for (int j = 0; j < NUM_LEDS; j++)
            {
                segments[i][j] = CHSV(hue, 255, 255);
            }
        }
        FastLED.show();
        hue++;
        Serial.println(millis() - timestamp);
        timestamp = millis();

    }

    private:
    byte hue = 0;
    unsigned long timestamp = 0;

};

#endif