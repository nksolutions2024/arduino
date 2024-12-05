#include <Wire.h>

void setup() {
  // Start Serial communication for debugging
  Serial.begin(115200);

  // Initialize I2C communication as Master
  Wire.begin();

  delay(1000);  // Wait for slave to initialize
}

void loop() {
  // Data to send to the slave
  String dataToSend = "time1655";

  // Start I2C transmission to slave address 8
  Wire.beginTransmission(8);  // Slave address is 8
  Wire.write(dataToSend.c_str()); // Send string as bytes
  Wire.endTransmission();  // End transmission

  // Print sent data for debugging
  Serial.println("Sent Data: " + dataToSend);

  delay(2000);  // Wait 2 seconds before sending again
}
