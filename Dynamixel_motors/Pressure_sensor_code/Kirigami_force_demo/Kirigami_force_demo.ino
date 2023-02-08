//    FILE: HX_kitchen_scale.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711 demo
//     URL: https://github.com/RobTillaart/HX711


// to be tested

#include "HX711.h"
#include "MedianFilterLib2.h"

// **************************************

MedianFilter2<float> medianFilter1(10);
MedianFilter2<float> medianFilter2(10);

float raw_pressure_1 = 0;
float raw_pressure_2 = 0;
float raw_pressure_1_calibration = 0;
float raw_pressure_2_calibration = 0;
float raw_average_pressure = 0;
float predicted_force = 0;

// **************************************

HX711 scale;
HX711 scale_2;

uint8_t dataPin = 5;
uint8_t clockPin = 6;

uint8_t dataPin_2 = 9;
uint8_t clockPin_2 = 10;

float weight_measurement = 0;
float weight_measurement_2 = 0;


// **************************************

void setup()
{
  Serial.begin(9600);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(HX711_LIB_VERSION);
  Serial.println();

  scale.begin(dataPin, clockPin);
  scale_2.begin(dataPin_2, clockPin_2);

  //A scale factor of 210.67 is found to work the best
  scale.set_scale(31.71);       // TODO you need to calibrate this yourself.
  scale.tare();

  scale_2.set_scale(31.71);       // TODO you need to calibrate this yourself.
  scale_2.tare();

//  Serial.println("CLEARSHEET");

  for (int i = 0; i < 10; i++){
    // Make raw measurement from the pressure sensors and calculate average
    raw_pressure_1_calibration = medianFilter1.AddValue(analogRead(A0));
    raw_pressure_2_calibration = medianFilter2.AddValue(analogRead(A1));
  }
}


void loop()
{
  // read 1 times to get average
  // Measurement made in newtons
  weight_measurement = scale.get_units(1)/1000*9.81;
  weight_measurement_2 = scale_2.get_units(1)/1000*9.81;
  
  // Make raw measurement from the pressure sensors and calculate average
  raw_pressure_1 = medianFilter1.AddValue(analogRead(A0));
  raw_pressure_2 = medianFilter2.AddValue(analogRead(A1));
  raw_average_pressure = (raw_pressure_1 + raw_pressure_2) / 2;
  predicted_force = 1.5789*raw_average_pressure - 50;

  Serial.print("DATA,");
  Serial.print(weight_measurement+weight_measurement_2, 2);
  Serial.print(",");
  Serial.print(raw_pressure_1-raw_pressure_1_calibration);
  Serial.print(",");
  Serial.print(raw_pressure_2-raw_pressure_2_calibration);
  Serial.print(",");
  Serial.print(raw_pressure_1+raw_pressure_2-raw_pressure_1_calibration-raw_pressure_2_calibration);
  Serial.print(",");
  Serial.println(predicted_force);

}
