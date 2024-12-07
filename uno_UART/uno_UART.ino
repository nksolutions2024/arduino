void setup() {
  // Initialize the UART communication at 9600 baud rate
  Serial.begin(115200);
  while (!Serial) {
    // Wait for the serial port to connect. Needed for native USB port only.
  }

  Serial.println("UART Communication Initialized");
}

void loop() {
  // Check if there is incoming data from the UART
  if (Serial.available() > 0) {
    // Read the incoming data
    char receivedChar = Serial.read();

    // Echo the received data back to the sender
    Serial.print("Received: ");
    Serial.println(receivedChar);

    // Perform additional processing if needed
    if (receivedChar == 'a') {
      Serial.println("You sent the letter 'a'!");
    }
  }

  // Send data to the UART every 2 seconds (optional)
  delay(2000);
  Serial.println("hhello1634");
}
