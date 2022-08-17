#include <Leds.h>
#include <Sensor.h>

class Perla {
    public:
    vector<vector<float>> levels = vector<vector<float>>(NUM_SEGMENTS, vector<float>(NUM_COLS_PER_SEGMENT));
    void setup();
    void tick(vector<Sensor>& array);
    float decreaseFactor = 80;  // brightness to decrease per second on sensor level 0%
    float increaseFactor = 10;  // brightness to increase after each firing
    double probabilityFactor = 0.8;  // probability to fire per second on level 100%

    private:
    unsigned long _lastTimestamp = 0;
};
