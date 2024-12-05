#include <Wire.h>

#define SLAVE_ADDRESS 8  // I2C Slave address (match this on the slave device)

void setup() {
  Serial.begin(115200);
  Wire.begin();  // Start the I2C as master
  Serial.println("I2C Master Ready!");
}

void loop() {
  Wire.requestFrom(SLAVE_ADDRESS, 16); // Request 16 bytes from slave device
  
  while (Wire.available()) {
    char c = Wire.read();  // Read the byte received
    Serial.print(c);  // Print the byte to Serial Monitor
  }
  
  delay(1000);  // Wait for 1 second before next request
}
