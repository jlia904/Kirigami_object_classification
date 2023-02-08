/*
  Darren Lewis calculated pressure readings MPX5010 baed on datasheet
  datasheet: https://docs.rs-online.com/9979/0900766b8138443c.pdf
  my website: http://darrenlewismechatronics.co.uk/
*/

float pressure_1 = analogRead(A0);
float pressure_2 = analogRead(A1);
float pressure_1_tare = 0;
float pressure_2_tare = 0;
float average_pressure = 0;
float alpha = 0.01;
int incoming_data = 0;

void setup() {
  Serial.begin(57600);
  pinMode(13, OUTPUT);
  
  for (int i = 0; i < 2000; i++){
    pressure_1 = pressure_1 * (1-alpha) + alpha *analogRead(A0);
    pressure_2 = pressure_2 * (1-alpha) + alpha *analogRead(A1);
  }

  pressure_1_tare = pressure_1;
  pressure_2_tare = pressure_2;
  digitalWrite(13, HIGH);  

}

void loop() {

  incoming_data = Serial.read();
  
  if (incoming_data == '1') {
    digitalWrite(13, HIGH);    
    pressure_1_tare = pressure_1;
    pressure_2_tare = pressure_2;
  }
  else if (incoming_data == '0'){
    digitalWrite(13, LOW);    
    pressure_1_tare = 0;
    pressure_2_tare = 0;
  }
  else if (incoming_data == '2'){
    Serial.print(pressure_1 - pressure_1_tare);
    Serial.print(",");
    Serial.println(pressure_2 - pressure_2_tare);
  }
  
  pressure_1 = pressure_1 * (1-alpha) + alpha *analogRead(A0);
  pressure_2 = pressure_2 * (1-alpha) + alpha *analogRead(A1);
  
  Serial.print(pressure_1 - pressure_1_tare);
  Serial.print(" ");
  Serial.println(pressure_2 - pressure_2_tare);

}
