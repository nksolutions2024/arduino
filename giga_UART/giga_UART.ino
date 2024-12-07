void setup() {
  Serial.begin(115200);
  Serial2.begin(115200); //important TX1 

  Serial.println("UART Communication Initialized");
}

void loop() {
  delay(2000);
  Serial.println("giga serial monitor");
  Serial2.println("giga sending time1703");
  
}
