#ifndef SENSOR_H_INCLUDED
#define SENSOR_H_INCLUDED

// some code taken from: https://gist.github.com/WoLpH/0094b278a54f8f472c76b7eb0d0a8f89

using namespace std;
#include <list>

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
    void (*_callback)(); // function with no parameters that must call the array instance `echo()`

    void setup(void (*callback)());
    void add(Sensor sensor);
    void ping();
    void echo();
    void next();

    // set timer
    // read sensor
    // goto next

};

#endif
