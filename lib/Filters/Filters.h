#ifndef FILTERS_H_INCLUDED
#define FILTERS_H_INCLUDED

#include <math.h>
#include <Arduino.h>

#define MAX_DISTANCE 200
#define MIN_DISTANCE 16


class Filter
{
public:
    unsigned long raw = 0;
    double measurament;
    double filtered = 0;
    double level = 0;

    int newValue(unsigned long value);

private:
    ///// First order filter /////
    ///// and ignore first zeroes /////
    const double alpha = 0.2;
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