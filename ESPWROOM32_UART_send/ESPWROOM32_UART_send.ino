void setup() {
  Serial.begin(115200);

  // Wait here for the serial monitor to open (needed for some boards)
  while (!Serial) {
  }

  Serial.println("ESPWROOM32 UART Sender");
}

void loop() {
  Serial.println("ESPWROOM32 serial monitor1647");
  delay(1000);

  // // Receiver: Check if there is incoming data from UART
  // if (Serial.available() > 0) {
  //   // Read the incoming data
  //   String receivedData = Serial.readString();

  //   // Print received data to the serial monitor
  //   Serial.print("Received: ");
  //   Serial.println(receivedData);
  // }
}
