#ifndef SENSOR_H_INCLUDED
#define SENSOR_H_INCLUDED

// some code taken from: https://gist.github.com/WoLpH/0094b278a54f8f472c76b7eb0d0a8f89

using namespace std;
#include <list>

#include <math.h>
#include <NewPing.h>


#define MAX_DISTANCE 200
#define MIN_DISTANCE 16

class NewPingInterrupt : public NewPing {
    public:

    using NewPing::NewPing;
    unsigned long ping_cm(void (*callback)());
    void echo();
    void stop();
};

class Sensor
{
public:

    uint8_t pin;
    unsigned int distanceCm;

    NewPingInterrupt newPing;

    // init the sonar
    Sensor(uint8_t pin);

    void setup();
};



class SensorArray
{
    public:

    list<Sensor> array;
    list<Sensor>::iterator currentSensor;
    bool reading = false;

    void setup();
    void add(Sensor sensor);
    void ping(void (*callback)());
    void echo();
    void next();

    // set timer
    // read sensor
    // goto next

};

class Filter
{
    unsigned long raw = 0;
    double measurament;
    double filtered = 0;
    double level = 0;

    int newValue(unsigned long value);

private:
    ///// First order filter /////
    ///// and ignore first zeroes /////
    const double alpha = 0.05;
    const int zeroes_threshold = 15;
    int zeroes_count = 0;

    unsigned long startTime = 0;
    int duration = 60;

    ///// Higher output on closer distance /////
    ///// multiplier * ln(MAX_DISTANCE/x) ////
    ///// 40 * ln(200/cm) ////
    const double multiplier = 40; // good results for 2m = 100 at 16cm

    void printDebug();

};

#endif
