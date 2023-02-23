//    FILE: HX_kitchen_scale.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711 demo
//     URL: https://github.com/RobTillaart/HX711

#include "HX711.h"

HX711 scale_1, scale_2;

uint8_t dataPin_1 = 5;
uint8_t clockPin_1 = 6;
uint8_t dataPin_2 = 7;
uint8_t clockPin_2 = 8;

float w1, w2 = 0;

float pressure_1 = analogRead(A1);
float pressure_2 = analogRead(A0);
float pressure_1_tare = 0;
float pressure_2_tare = 0;
float alpha = 0.5;

void setup()
{
  Serial.begin(57600);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(HX711_LIB_VERSION);
  Serial.println();

  scale_1.begin(dataPin_1, clockPin_1);
  scale_2.begin(dataPin_2, clockPin_2);

  //A scale factor of 466.8, -473 is found to work the best
  scale_1.set_scale(-3200.48);       // -3200.48, -3177.05
  scale_1.tare();

  scale_2.set_scale(3177.05);       // -3200.48, -3177.05
  scale_2.tare();

  for (int i = 0; i < 200; i++){
    pressure_1 = pressure_1 * (1-alpha) + alpha *analogRead(A1);
    pressure_2 = pressure_2 * (1-alpha) + alpha *analogRead(A0);
  }  

  pressure_1_tare = pressure_1;
  pressure_2_tare = pressure_2;
  
}


void loop()
{
  pressure_1 = pressure_1 * (1-alpha) + alpha *analogRead(A1);
  pressure_2 = pressure_2 * (1-alpha) + alpha *analogRead(A0);

  w1 = scale_1.get_units(1);
  w2 = scale_2.get_units(1);

  Serial.print(w1);
  Serial.print(",");
  Serial.print(w2);
  Serial.print(",");
  Serial.print(pressure_1 - pressure_1_tare);
  Serial.print(",");
  Serial.println(pressure_2 - pressure_2_tare);
  delay(50);
}

