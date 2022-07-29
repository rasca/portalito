#include <Arduino.h>
#include <Sensor.h>

// sensors pins
// 32 33 25 26 27



SensorArray sensorArray;

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
  sensorArray.setup();
}


void loop() {
  // delay(100);
  // Serial.print("s1 response: ");
  // Serial.print(s1.ping_cm());

  // delay(100);
  // Serial.print(" s2 response: ");
  // Serial.print(s2.ping_cm());

  // delay(100);
  // Serial.print(" s3 response: ");
  // Serial.print(s3.ping_cm());

  delay(100);
  sensorArray.ping(sensorEcho);

  // Serial.print("Ping response: ");
  // unsigned int time = sensor.start_ping();
  // Serial.println(time);
  /*
  if (millis() - start > 400) {
    for (auto it = sensorArray.array.begin(); it != sensorArray.array.end(); ++it)
    {
      Serial.print(it->raw);
      Serial.print(" ");
    }
    Serial.println();

    sensorArray.pulse();
    start = millis();
  }
  */
}
