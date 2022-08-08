#include <Arduino.h>
#include <Sensor.h>
#include <Leds.h>
#include <Boa.h>

// sensors pins
// 32 33 25 26 27

// light pins
// 16 17 5 18 19

SensorArray sensorArray;
Leds leds;
Sonar sonar;
CircularWave circularWave;
Align align;
Boa boa;

void IRAM_ATTR sensorEcho() {
    sensorArray.echo();
}

void setup() {
  Serial.begin(9600);

  sensorArray.add(Sensor(25));
  sensorArray.add(Sensor(26));
  sensorArray.add(Sensor(27));
  sensorArray.add(Sensor(32));
  sensorArray.add(Sensor(33));
  sensorArray.setup(sensorEcho);

  leds.setup();
}

unsigned long start = 0;

void loop() {

  if (millis() - start > 20) {
    sensorArray.ping();
    start = millis();
  }

  FastLED.clear();
  // leds.tick();
  // align.tick();
  boa.tick();
  sonar.tick();
  // circularWave.tick();
  FastLED.show();
}
