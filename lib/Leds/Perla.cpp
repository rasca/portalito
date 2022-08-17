#include <Perla.h>

void Perla::tick(vector<Sensor>& array)
{
    unsigned long timestamp = millis();
    unsigned long currentMillis = timestamp - _lastTimestamp;
    _lastTimestamp = timestamp;

    // paint all leds based on levels
    // and decrease current level for all the leds

    float segmentLevel = 0;
    double probability = 0;
    for (int i=0; i<NUM_SEGMENTS; i++)
    {
        segmentLevel = array[i].newPing.filter.level;
        for (int j=0; j<NUM_COLS_PER_SEGMENT; j++)
        {
            CRGB color = CRGB::Crimson; // TODO: choose a color from pallete

            // calculate possibility of firing
            probability = (0.01 + segmentLevel / 100.0) * probabilityFactor * (currentMillis / 1000.0);;
            // if (i == 0 && j <1){
            //     Serial.print("currentMillis: ");
            //     Serial.print(currentMillis);
            //     Serial.print("\tprobability: ");
            //     Serial.print(probability);
            //     Serial.print("\tsegmentLevel: ");
            //     Serial.print(segmentLevel);
            //     Serial.print("\tlevel: ");
            //     Serial.println(levels[i][j]);
            // }
            if ((double)rand() / RAND_MAX < probability)
            {
                levels[i][j]= min(255.0f, increaseFactor + levels[i][j]);
                // completely paint when firing
                paintColumn(i * NUM_COLS_PER_SEGMENT + j, color);
            } else {
                // paint all the columns based on level
                paintColumn(i * NUM_COLS_PER_SEGMENT + j, color.nscale8(levels[i][j]));
            }


            // Serial.print("printing Column: ");
            // Serial.print(i * NUM_COLS_PER_SEGMENT + j);
            // Serial.print("/tto level: ");
            // Serial.println(levels[i][j]);

            // if (i == 0 && j <2)
            // {
            //     Serial.print("segmentLevel: ");
            //     Serial.print(segmentLevel);
            //     Serial.print("\tprevious level: ");
            //     Serial.print(levels[i][j]);
            // }
            // decrease all the levels
            levels[i][j] = min(max(0.0f, levels[i][j] - (segmentLevel * -1 + 100) / 100.0f * decreaseFactor * (currentMillis / 1000.0f)), 255.0f);
            // if (i == 0 && j <2)
            // {
            //     Serial.print("\tdecrease: ");
            //     Serial.println((segmentLevel * -1 + 100) / 500.0f * currentMillis * decreaseFactor);
            //     Serial.print("\tlevel: ");
            //     Serial.println(levels[i][j]);
            // }
        }
    }
    // blink some
    //)
        // add values
    // decline all

}
