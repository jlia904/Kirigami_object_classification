#include "MedianFilterLib2.h"

/*
  Darren Lewis calculated pressure readings MPX5010 baed on datasheet
  datasheet: https://docs.rs-online.com/9979/0900766b8138443c.pdf
  my website: http://darrenlewismechatronics.co.uk/
*/
MedianFilter2<float> medianFilter1(10);
MedianFilter2<float> medianFilter2(10);

float pressure_1 = 0;
float pressure_2 = 0;
float average_pressure = 0;


void setup() {
  Serial.begin(19200);
}

void loop() {

  pressure_1 = medianFilter1.AddValue(analogRead(A0));
  pressure_2 = medianFilter2.AddValue(analogRead(A1));
  average_pressure = (pressure_1 + pressure_2) / 2;
  
  Serial.println(average_pressure);
  
}
