int var5=1;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);  //important TX1

  Serial.println("UART Communication Initialized");
}

void loop() {
  Serial.println("giga-serial-monitor1436");
  Serial.println(var5);

  // Serial2.println("giga-Counter:");
  Serial2.println(var5);
  var5=var5+1;


  String incoming;
  while (Serial2.available()) {
    delay(2);
    char c = Serial2.read();
    incoming += c;
  }
  Serial.println(incoming);

  delay(2000);
}
