int incoming_data = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  pinMode(13, OUTPUT);
}

void loop() {

    // Read data from debug serial to set motor position
  incoming_data = Serial.read();
  if (incoming_data == '1') {
    digitalWrite(13, HIGH);    
  }
  else if (incoming_data == '2'){
    digitalWrite(13, LOW);    
  }
  // // put your main code here, to run repeatedly:
  // _delay_ms(1000);
  // digitalWrite(13, HIGH);
  // _delay_ms(1000);
  // digitalWrite(13, LOW);

}
