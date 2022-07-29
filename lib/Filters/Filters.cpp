#include <Filters.h>

int Filter::newValue(unsigned long value)
{
    raw = value;
    measurament = value;

    // disregard first (zero_threshold)
    if (measurament == 0)
    {
        zeroes_count++;
    }
    else
    {
        zeroes_count = 0;
    }

    // clamp to MIN_DISTANCE
    if (measurament < MIN_DISTANCE && measurament > 0)
    {
        measurament = MIN_DISTANCE;
    }

    // if we have a measurement update the filter
    if (zeroes_count == 0)
    {
        // use the measurement
        filtered = filtered * (1 - alpha) + measurament * alpha;
    }
    else if (zeroes_count > zeroes_threshold)
    // if we have enough zeros update the filter
    {
        // multiple zeros. reading should be MAX_DISTANCE
        filtered = filtered * (1 - alpha) + MAX_DISTANCE * alpha;
    }

    // perform ln(1/x) transformation
    // filtered is at least MIN_DISTANCE (no division by zero)
    level = multiplier * log(MAX_DISTANCE / filtered);

    if (level > 100)
    {
        level = 100;
    }

    // printDebug();

    return level;
}


void Filter::printDebug()
{
    Serial.print("measurament: ");
    Serial.print(measurament);
    Serial.print(" smooth: ");
    Serial.print(filtered);
    Serial.print(" level: ");
    Serial.println(level);
}
