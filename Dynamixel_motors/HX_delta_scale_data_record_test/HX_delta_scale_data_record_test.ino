//    FILE: HX_kitchen_scale.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711 demo
//     URL: https://github.com/RobTillaart/HX711

#include "HX711.h"

HX711 scale;

uint8_t dataPin = 7;
uint8_t clockPin = 8;

float w1, w2 = 0;


void setup()
{
  Serial.begin(57600);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(HX711_LIB_VERSION);
  Serial.println();

  scale.begin(dataPin, clockPin);

  scale.set_scale();
  scale.tare();
  Serial.println("Please place the calibration weight of 100g");
  delay(3000);
  long calibration_reading = scale.get_units(10);

  Serial.print("Scale factor is: ");
  Serial.println(float(calibration_reading)/100);

  //A scale factor of 466.8, -473 is found to work the best
  scale.set_scale(466.8);       // -3200.48, -3177.05
  scale.tare();
}


void loop()
{
  w1 = scale.get_units(5);
  Serial.print("Weight = ");
  Serial.print("DATA,");
  Serial.print(w1);
  Serial.println("g");
  delay(200);
}

