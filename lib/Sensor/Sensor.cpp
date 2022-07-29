using namespace std;
#include <Sensor.h>

// #define DEBUG_SENSOR


Sensor::Sensor(uint8_t pin) : pin(pin), newPing(pin, pin, MAX_DISTANCE) {
}

void Sensor::setup() {
}

unsigned long NewPingInterrupt::ping_cm(void (*callback)())
{

#ifdef DEBUG_SENSOR
    Serial.print("s");
    Serial.print(_echoPin);
    Serial.print(": ");
#endif

    if (!ping_trigger())
        return NO_ECHO; // Trigger a ping, if it returns false, return NO_ECHO to the calling function.

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

#ifdef DEBUG_SENSOR
    Serial.print(distanceCm);
    Serial.print("; ");
#endif
}

void NewPingInterrupt::stop() {
    detachInterrupt(digitalPinToInterrupt(_echoPin));
#ifdef DEBUG_SENSOR
    Serial.print("echo NO_ECHO");
#endif
}



void SensorArray::setup(void (*callback)()) {
    _callback = callback;
    currentSensor = array.begin();
}

void SensorArray::add(Sensor sensor) {
    array.push_back(sensor);
}

void SensorArray::ping() {
    if (reading) {
        currentSensor->newPing.stop();
        next();
    }
    reading = true;
    currentSensor->newPing.ping_cm(_callback);
}

void SensorArray::next() {
    currentSensor++;
    if (currentSensor == array.end()) {
        currentSensor = array.begin();
#ifdef DEBUG_SENSOR
        Serial.println(" ");
#endif
    }
}

void SensorArray::echo() {
    reading = false;
    currentSensor->newPing.echo();
    next();
}