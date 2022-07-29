#include <Leds.h>
#include <Utils.h>

std::array<std::array<CRGB, NUM_LEDS>, NUM_SEGMENTS> segments;

void Leds::setup()
{
    // LEDS
    // 16 17 5 18 19
    FastLED.addLeds<WS2812, GPIO_NUM_16>(segments[0].data(), NUM_LEDS);
    FastLED.addLeds<WS2812, GPIO_NUM_17>(segments[1].data(), NUM_LEDS);
    FastLED.addLeds<WS2812, GPIO_NUM_5>(segments[2].data(), NUM_LEDS);
    FastLED.addLeds<WS2812, GPIO_NUM_18>(segments[3].data(), NUM_LEDS);
    FastLED.addLeds<WS2812, GPIO_NUM_19>(segments[4].data(), NUM_LEDS);
    FastLED.setBrightness(204);
}

void Leds::tick()
{
    for (int i = 0; i < NUM_SEGMENTS; i++)
    {
        for (int j = 0; j < NUM_LEDS; j++)
        {
            segments[i][j] = CHSV(hue, 255, 255);
        }
    }
    hue++;
}

#include <cmath>

void paintColumn(int column, CRGB color)
{
    int segment = column / NUM_COLS_PER_SEGMENT;
    int first_led = (column % NUM_COLS_PER_SEGMENT) * (NUM_COL_LEDS + NUM_EXTRA_BOTTOM_LEDS / 2);
    if (column % 2 == 1) {
        first_led += NUM_EXTRA_BOTTOM_LEDS / 2;
    }
    Serial.print(" column: ");
    Serial.print(column);
    Serial.print(" segment: ");
    Serial.print(segment);
    Serial.print(" first_led: ");
    Serial.print(first_led);
    Serial.print(" ");
    for (int i=0; i< NUM_COL_LEDS; i++) {
        segments[segment][i + first_led] = color;
    }
}

void Sonar::setup() {}

void Sonar::tick() {
    // advance the sonar angle based on speed
    unsigned long timestamp = millis();
    angle = fmod((angle + (timestamp - _lastTimestamp) / (1.0 / speed)), 360.0);
    _lastTimestamp = timestamp;

    Serial.print(" angle: ");
    Serial.print(angle);

    // redraw the sonar line
    // which column do we need to colour?
    double column_position = fmod((angle / (360.0 / (NUM_COLS_PER_SEGMENT * NUM_SEGMENTS))), 360.0);
    int first_column= floor(column_position);
    int second_column = (first_column + 1) % (NUM_COLS_PER_SEGMENT * NUM_SEGMENTS);
    double closeness = column_position - first_column;

    int intensity = doubleMap(closeness, 0, 1, 255, 0);

    Serial.print(" FIRST");
    paintColumn(first_column, CHSV(85, 255, intensity));

    Serial.print(" SECOND");
    paintColumn(second_column, CHSV(85, 255, 255 - intensity));
    Serial.println();

}