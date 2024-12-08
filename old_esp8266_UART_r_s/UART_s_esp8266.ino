void setup() {
  // Initialize the hardware serial communication (UART) at 115200 baud
  Serial.begin(115200);
  
  // Wait for the serial port to initialize
  while (!Serial) {
    ; // Wait here for the serial monitor to open (needed for some boards)
  }
  
  Serial.println("ESP8266 UART Sender and Receiver Example");
}

void loop() {
  // Sender: Send data to UART
  Serial.println("time1828");
  delay(1000);  // Delay to control the frequency of sending data
  
  // Receiver: Check if there is incoming data from UART
  if (Serial.available() > 0) {
    // Read the incoming data
    String receivedData = Serial.readString();
    
    // Print received data to the serial monitor
    Serial.print("Received: ");
    Serial.println(receivedData);
  }
}
