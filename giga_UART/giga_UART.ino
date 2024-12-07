void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);

  while (!Serial) {
  }

  Serial.println("UART Communication Initialized");
}

void loop() {


  // Send data to the UART every 2 seconds (optional)
  delay(2000);
  Serial.println("hhello1634");
  Serial2.println("giga sending time1659");
  
}
