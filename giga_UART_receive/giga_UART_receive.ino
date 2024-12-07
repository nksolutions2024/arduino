void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);  //important TX1

  Serial.println("UART Communication Initialized");
}

void loop() {
  delay(2000);
  // Serial2.println("giga sending time1703");
  Serial.println("giga serial monitor");

  String incoming;
  while (Serial2.available()) {
    delay(2);
    char c = Serial2.read();
    incoming += c;
  }
  Serial.println(incoming);
  
}
