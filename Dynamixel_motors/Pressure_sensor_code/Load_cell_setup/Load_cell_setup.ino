//    FILE: HX_kitchen_scale.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711 demo
//     URL: https://github.com/RobTillaart/HX711


// to be tested

#include "HX711.h"

HX711 scale;

uint8_t dataPin = 5;
uint8_t clockPin = 6;

float measurement = 0;


void setup()
{
  Serial.begin(9600);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(HX711_LIB_VERSION);
  Serial.println();

  scale.begin(dataPin, clockPin);

  //A scale factor of 210.67 is found to work the best
  scale.set_scale(31.71);       // TODO you need to calibrate this yourself.
  scale.tare();

//  Serial.println("CLEARSHEET");
}


void loop()
{
  // read 1 times to get average
  measurement = scale.get_units(1);
  Serial.println("Weight = ");
  Serial.print("DATA,");
  Serial.println(measurement/1000*9.81, 4);
//  Serial.println("g");
  delay(10);
}


// -- END OF FILE --
