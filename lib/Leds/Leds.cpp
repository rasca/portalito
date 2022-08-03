#include <Leds.h>
#include <Utils.h>

std::array<std::array<CRGB, NUM_LEDS>, NUM_SEGMENTS> segments;

void Leds::setup()
{
    // LEDS
    // 16 17 5 18 19
    FastLED.addLeds<WS2812, GPIO_NUM_16>(segments[0].data(), NUM_LEDS);
    // FastLED.addLeds<WS2812, GPIO_NUM_17>(segments[1].data(), NUM_LEDS);
    // FastLED.addLeds<WS2812, GPIO_NUM_5>(segments[2].data(), NUM_LEDS);
    // FastLED.addLeds<WS2812, GPIO_NUM_18>(segments[3].data(), NUM_LEDS);
    // FastLED.addLeds<WS2812, GPIO_NUM_19>(segments[4].data(), NUM_LEDS);
    FastLED.setBrightness(180);
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

void paintPixel(int column, int row, CRGB color)
{
    if (column < 0)
        column += NUM_COLS;
    column = column % NUM_COLS;
    int segment = column / NUM_COLS_PER_SEGMENT;
    int first_led = (column % NUM_COLS_PER_SEGMENT) * (NUM_COL_LEDS + NUM_EXTRA_BOTTOM_LEDS / 2);

    if (column % 2 == 1)
    {
        first_led += NUM_EXTRA_BOTTOM_LEDS / 2;
        segments[segment][first_led + NUM_COL_LEDS - row] = color;
        return;
    }
    segments[segment][first_led + row] = color;
}

void paintColumn(int column, CRGB color)
{
    int segment = column / NUM_COLS_PER_SEGMENT;
    int first_led = (column % NUM_COLS_PER_SEGMENT) * (NUM_COL_LEDS + NUM_EXTRA_BOTTOM_LEDS / 2);
    if (column % 2 == 1) {
        first_led += NUM_EXTRA_BOTTOM_LEDS / 2;
    }
    for (int i=0; i< NUM_COL_LEDS; i++) {
        segments[segment][i + first_led] = color;
    }
}

void paintColumnPointMirrored(int centerColumn, int centerRow, float y, int columnOffset) {
    // draw an interpolated pixel
    /*
    Serial.print("Painting Column Point Mirrored, y: ");
    Serial.print(y);
    Serial.print("  columnOffset ");
    Serial.print(columnOffset);
    */

    int yFloor = floor(y);
    int firstRow = centerRow - yFloor;
    int secondRow = firstRow - 1;
    // Serial.print("  firstRow ");
    // Serial.println(firstRow);
    float closeness = y - yFloor;
    int intensity = floatMap(closeness, 0, 1, 255, 0);

    if (firstRow > 0)
    {
        paintPixel(centerColumn + columnOffset, firstRow, CHSV(85, 255, intensity));
        paintPixel(centerColumn - columnOffset, firstRow, CHSV(85, 255, intensity));
    }
    if (secondRow > 0)
    {
        paintPixel(centerColumn + columnOffset, secondRow, CHSV(85, 255, 255 - intensity));
        paintPixel(centerColumn - columnOffset, secondRow, CHSV(85, 255, 255 - intensity));
    }

    firstRow = centerRow + yFloor;
    secondRow = firstRow + 1;

    if (firstRow < NUM_COL_LEDS)
    {
        paintPixel(centerColumn + columnOffset, firstRow, CHSV(85, 255, intensity));
        paintPixel(centerColumn - columnOffset, firstRow, CHSV(85, 255, intensity));
    }
    if (secondRow < NUM_COL_LEDS)
    {
        paintPixel(centerColumn + columnOffset, secondRow, CHSV(85, 255, 255 - intensity));
        paintPixel(centerColumn - columnOffset, secondRow, CHSV(85, 255, 255 - intensity));
    }

}

void paintCircle (int centerColumn, int centerRow, double distance) {
    // draw a circle of distance radius from (centerColumn, centerRow)
    // the distance between two leds are 1 unit of distance both horizontally and vertically
    // circle equation: x^2 + y^2 = r^2
    // --> y = +- (r^2 - x^2)^(1/2)
    // we can ignore r^2, just increment it faster
    // y = +- (distance - column^2)^(1/2)

    /*
    Serial.println();
    Serial.print("print circle, distance: ");
    Serial.println(distance);
    */
    
    // iterate over each column = x
    float y;
    for (int i=0; i<distance; i++)
    {
        // calculate y
        y = sqrt(distance * distance - i * i);

        // interpolate y and paint 
        paintColumnPointMirrored(centerColumn, centerRow, y, i);
    }


    // TODO: improve the shape of the flanera using ellipse / egg equation
    // ellipse equation: : x^2 / a + y^2 / b = r2
    // --> y = +- (r^2 - x^2)^(1/2)

    // egg equation: : x^2 * t(y) / a  + y^2 / b = r2
    // --> y = +- ((r^2 - x^2 * t(y) / a) * b)^(1/2)
}

void Align::setup() {}

void Align::tick()
{

    paintPixel(0, 17, CRGB::Red);
    paintPixel(1, 17, CRGB::Red);
    paintPixel(2, 17, CRGB::Red);
    paintPixel(3, 17, CRGB::Red);
    paintPixel(4, 17, CRGB::Red);
    paintPixel(5, 17, CRGB::Red);
    paintPixel(6, 17, CRGB::Red);
    paintPixel(7, 17, CRGB::Red);
    paintPixel(8, 17, CRGB::Red);
    paintPixel(9, 17, CRGB::Red);

    paintPixel(0, 35, CRGB::Blue);
    paintPixel(1, 35, CRGB::Blue);
    paintPixel(2, 35, CRGB::Blue);
    paintPixel(3, 35, CRGB::Blue);
    paintPixel(4, 35, CRGB::Blue);
    paintPixel(5, 35, CRGB::Blue);
    paintPixel(6, 35, CRGB::Blue);
    paintPixel(7, 35, CRGB::Blue);
    paintPixel(8, 35, CRGB::Blue);
    paintPixel(9, 35, CRGB::Blue);
}

void Sonar::setup() {}

void Sonar::tick() {
    // advance the sonar angle based on speed
    unsigned long timestamp = millis();
    angle = fmod((angle + (timestamp - _lastTimestamp) / (1.0 / speed)), 360.0);
    _lastTimestamp = timestamp;

    // Serial.print(" angle: ");
    // Serial.print(angle);

    // redraw the sonar line
    // which column do we need to colour?
    double column_position = fmod((angle / (360.0 / NUM_COLS)), 360.0);
    int first_column= floor(column_position);
    int second_column = (first_column + 1) % NUM_COLS;
    double closeness = column_position - first_column;

    int intensity = doubleMap(closeness, 0, 1, 255, 0);

    // Serial.print(" FIRST ");
    // Serial.print(first_column);
    paintColumn(first_column, CHSV(85, 255, intensity));

    // Serial.print(" SECOND ");
    // Serial.print(second_column);
    paintColumn(second_column, CHSV(85, 255, 255 - intensity));
    // Serial.println();

}

void CircularWave::setup() {}

void CircularWave::tick() {
    // advance the sonar angle based on speed
    unsigned long timestamp = millis();
    previousAngle = angle;
    angle = fmod((angle + (timestamp - _lastTimestamp) / (1.0 / angleSpeed)), 360.0);
    amplitude = (amplitude + (timestamp - _lastTimestamp) / (1.0 / speed));
    _lastTimestamp = timestamp;
    Serial.println(angle);

    // a new cycle
    if (circularWave == false && angle < previousAngle)
    {
        circularWave = true;
        amplitude = 0;
    }
    if (amplitude > maxAmplitude)
    {
        circularWave = false;
    }
    if (circularWave)
    {
        paintCircle(5, 17, amplitude);
    }

}