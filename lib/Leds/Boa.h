#include <Leds.h>

class Boa {
    public:
    double speed = 0.4;  // speed at which the boa moves
    int initialColumn = 10;  // in which column to start the spread
    int tailColumns = 6;  // how many columns the fade will last
    int tailFade = 200;  // 0..255 how fast it fades in previous columns
    int launchInterval = 4000;  // in millis, how often do we repeat the effect
    int cycles = 2; // how many cicles per interval

    void setup();
    void tick();

    private:
    unsigned long _lastTimestamp = 0;
    double angle = 0;
    int _currentCycle = 0;
    unsigned long _lastCycleStart = 0;

};
