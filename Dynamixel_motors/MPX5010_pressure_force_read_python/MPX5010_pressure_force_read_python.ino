/*
  Darren Lewis calculated pressure readings MPX5010 baed on datasheet
  datasheet: https://docs.rs-online.com/9979/0900766b8138443c.pdf
  my website: http://darrenlewismechatronics.co.uk/
*/

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

float scale_factor_1 = -466.8;
float scale_factor_2 = 473;

float pressure_1 = analogRead(A0);
float pressure_2 = analogRead(A1);
float pressure_1_tare = 0;
float pressure_2_tare = 0;
float average_pressure = 0;
float alpha = 0.2;
int incoming_data = 0;

void setup() {
  Serial.begin(57600);
  pinMode(13, OUTPUT);
  
  scale_1.begin(dataPin_1, clockPin_1);
  scale_2.begin(dataPin_2, clockPin_2);
  
  scale_1.set_scale(scale_factor_1);
  scale_2.set_scale(scale_factor_2);

  scale_1.tare();
  scale_2.tare();

  for (int i = 0; i < 2000; i++){
    pressure_1 = pressure_1 * (1-alpha) + alpha *analogRead(A0);
    pressure_2 = pressure_2 * (1-alpha) + alpha *analogRead(A1);
  }
  
  pressure_1_tare = pressure_1;
  pressure_2_tare = pressure_2;
  digitalWrite(13, HIGH);  

}

// void send_data(float data_1, float data_2){
//   if (data_1 < 100){
//       if (data_1 < 10){
//         Serial.print("00");
//       }
//       else{
//         Serial.print("0");     
//       }
//     }

//     Serial.print(data_1, 2);
//     Serial.print(",");

//     if (data_2 < 100){
//       if (data_2 < 10){
//         Serial.print("00");
//       }
//       else{
//         Serial.print("0");
//       }
//     }
    
//     Serial.println(data_2, 2);  
// }

void send_data(float data_1, float data_2, float data_3, float data_4){
  if (data_1 < 100){
      if (data_1 < 10){
        Serial.print("00");
      }
      else{
        Serial.print("0");     
      }
    }

    Serial.print(data_1, 1);
    Serial.print(",");

    if (data_2 < 100){
      if (data_2 < 10){
        Serial.print("00");
      }
      else{
        Serial.print("0");
      }
    }
    
    Serial.print(data_2, 1);
    Serial.print(",");  
    
    if (data_3 < 1000){
      if (data_3 < 100){
        if(data_3 < 10){
          Serial.print("000");
        }
        else{
          Serial.print("00");
        }
      }
      else{
        Serial.print("0");
      }
    }
    
    Serial.print(data_3, 1);
    Serial.print(","); 

    if (data_4 < 1000){
      if (data_4 < 100){
        if(data_4 < 10){
          Serial.print("000");
        }
        else{
          Serial.print("00");
        }
      }
      else{
        Serial.print("0");
      }
    }
    
    Serial.println(data_4, 1);


}


void loop() {

  incoming_data = Serial.read();
  
  if (incoming_data == '1') {
    digitalWrite(13, HIGH);    
    pressure_1_tare = pressure_1;
    pressure_2_tare = pressure_2;
    scale_1.tare(2);
    scale_2.tare(2);
    send_data(pressure_1 - pressure_1_tare, pressure_2 - pressure_2_tare, scale_1.get_units(1), scale_2.get_units(1));
    
  }
  else if (incoming_data == '0'){
    digitalWrite(13, LOW);    
    pressure_1_tare = 0;
    pressure_2_tare = 0;
    scale_1.tare(2);
    scale_2.tare(2);
    send_data(pressure_1 - pressure_1_tare, pressure_2 - pressure_2_tare, scale_1.get_units(1), scale_2.get_units(1));
    
  }
  else if (incoming_data == '2') {
    digitalWrite(13, HIGH);
    send_data(pressure_1 - pressure_1_tare, pressure_2 - pressure_2_tare, scale_1.get_units(1), scale_2.get_units(1));
  }
  
  pressure_1 = pressure_1 * (1-alpha) + alpha * analogRead(A0);
  pressure_2 = pressure_2 * (1-alpha) + alpha * analogRead(A1);
  
  // Serial.println(scale_2.get_units());

  // Serial.print(pressure_1 - pressure_1_tare);
  // Serial.print(" ");
  // Serial.println(pressure_2 - pressure_2_tare);
  
}
