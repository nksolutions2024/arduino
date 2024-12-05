#include <Wire.h>

String receivedData = ""; // Buffer to store received data

void setup() {
  Serial.begin(115200);

  // Initialize I2C communication as Slave
  Wire.begin(8); // Address of this slave device
  Wire.onReceive(receiveEvent);
}

void loop() {
  // Print received data
  if (receivedData.length() > 0) {
    Serial.println("Received Data: " + receivedData);
    receivedData = ""; // Clear buffer after processing
  }
  delay(100);
}

// Function to handle received data
void receiveEvent(int howMany) {
  char c;
  receivedData = ""; // Clear buffer
  while (Wire.available()) {
    c = Wire.read();  // Read each byte
    receivedData += c; // Append to buffer
  }
}