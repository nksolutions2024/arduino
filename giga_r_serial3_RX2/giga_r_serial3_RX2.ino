void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);  //important RX2

  Serial.println("UART Communication Initialized");
}

void loop() {
  delay(2000);
  // Serial3.println("giga sending time1703");
  Serial.println("giga serial monitor1659");

  String incoming;
  while (Serial3.available()) {
    delay(2);
    char c = Serial3.read();
    incoming += c;
  }
  Serial.println(incoming);
  
}
