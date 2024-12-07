#include <SoftwareSerial.h>

// Transmit using Hardware UART (UART0)
void setup() {
  // Initialize Serial with 115200 baud rate
  Serial.begin(115200);
  delay(1000);  // Allow time for initialization

  Serial.println("ESP8266 UART Communication Example");
}

void loop() {
  // Transmit a message
  Serial.println("Hello, this is ESP8266!");

  // Check if data is available to read
  if (Serial.available()) {
    // Read the incoming data
    String incomingData = Serial.readString();
    Serial.print("Received: ");
    Serial.println(incomingData);
  }

  delay(1000);  // Delay for readability
}
