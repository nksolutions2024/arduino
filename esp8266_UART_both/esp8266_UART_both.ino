void setup() {
  Serial.begin(115200);

  // Wait here for the serial monitor to open (needed for some boards)
  while (!Serial) {
  }

  Serial.println("ESP8266 UART Receiver");
}

void loop() {
  Serial.println("esp8266-sending-6821");

  // Receiver: Check if there is incoming data from UART
  if (Serial.available() > 0) {
    // Read the incoming data
    String receivedData = Serial.readString();

    // Print received data to the serial monitor
    Serial.print("Received data: ");  //comment it
    Serial.println(receivedData);     //comment it

  }

  delay(2000);
}
