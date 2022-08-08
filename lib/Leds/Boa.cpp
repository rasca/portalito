#include <Boa.h>

void Boa::setup() {}

void Boa::tick() {
    // advance the Boa angle based on speed
    unsigned long timestamp = millis();

    if (timestamp - _lastCycleStart > launchInterval) {
        _lastCycleStart = timestamp;
        angle = 0;
        _currentCycle = 0;
    }
    angle = fmod((angle + (timestamp - _lastTimestamp) / (1.0 / speed)), 360.0);
    _lastTimestamp = timestamp;
    if (_currentCycle >= cycles) {
        return;  // don't paint anuything if we are past the cycle
    }

    // how many columns have we advanced so far
    int columnOffset = floor(fmod((angle / (360.0 / NUM_COLS)), 360.0));

    CRGB color = CRGB::HotPink;
    for (int i=0; i < min(tailColumns, columnOffset); i++)
    {
        if (columnOffset - i < NUM_COLS /2)
        {
            paintExtra((initialColumn + columnOffset - i + NUM_COLS) % NUM_COLS, color);
            paintExtra((initialColumn - columnOffset + i + NUM_COLS) % NUM_COLS, color);
        }
        color.r = scale8(color.r, tailFade);
        color.g = scale8(color.g, tailFade);
        color.b = scale8(color.b, tailFade);

    }
    if (columnOffset > NUM_COLS / 2 + tailColumns)
    {
        _currentCycle++;
        angle = 0;
    }

}
