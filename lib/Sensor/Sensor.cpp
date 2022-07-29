using namespace std;
#include <Sensor.h>


#define MAX_DISTANCE 200
#define MIN_DISTANCE 16

Sensor::Sensor(uint8_t pin) : pin(pin), newPing(pin, pin, MAX_DISTANCE) {
}

void Sensor::setup() {
}

unsigned long NewPingInterrupt::ping_cm(void (*callback)()) {
    // return newPing.ping_cm();
    Serial.print("ping s");
    Serial.print(_echoPin);
    Serial.print("... ");
    if (!ping_trigger()) return NO_ECHO; // Trigger a ping, if it returns false, return NO_ECHO to the calling function.


    // Polling option
    // while (digitalRead(ECHO_PIN))                 // Wait for the ping echo.
    //     if (micros() > newPing._max_time) return NO_ECHO; // Stop the loop and return NO_ECHO (false) if we're beyond the set maximum distance.
    // return (micros() - (newPing._max_time - newPing._maxEchoTime) - PING_OVERHEAD) / US_ROUNDTRIP_CM; // Calculate ping time, include overhead.

    // Interrupt option
    attachInterrupt(digitalPinToInterrupt(_echoPin), callback, FALLING);
    // TODO: launch a timer to stop the reading

}

void NewPingInterrupt::echo() {
    unsigned long echoTime = (micros() - (_max_time - _maxEchoTime) - PING_OVERHEAD); // Calculate ping time, include overhead.
    unsigned long distanceCm = echoTime / US_ROUNDTRIP_CM;

    detachInterrupt(digitalPinToInterrupt(_echoPin));

    Serial.print("echo ");
    Serial.println(distanceCm);
}

void NewPingInterrupt::stop() {
    detachInterrupt(digitalPinToInterrupt(_echoPin));
    Serial.println("echo NO_ECHO");
}



void SensorArray::setup() {
    currentSensor = array.begin();
}

void SensorArray::add(Sensor sensor) {
    array.push_back(sensor);
}

void SensorArray::ping(void (*callback)()) {
    if (reading) {
        currentSensor->newPing.stop();
        next();
    }
    reading = true;
    currentSensor->newPing.ping_cm(callback);
}

void SensorArray::next() {
    currentSensor++;
    if (currentSensor == array.end()) {
        currentSensor = array.begin();
    }
}

void SensorArray::echo() {
    reading = false;
    currentSensor->newPing.echo();
    next();
}

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