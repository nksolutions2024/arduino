#include <Wire.h>

void setup() {
  Serial.begin(115200);

  // Initialize I2C communication as Master
  Wire.begin();
}

void loop() {
  // Request 1 byte from the Arduino
  Wire.requestFrom(8, 1);  // Request from slave with address 8

  if (Wire.available()) {
    byte status = Wire.read();
    // Print the status of each LED
    Serial.print("inside_if ");
    Serial.println(status);
  }
  Serial.println("outside_if");

  // Send data to Arduino Mega via I2C
  Wire.beginTransmission(8);         // Address of the slave (Mega)
  Wire.write("1708directly_written");  // Send string data
  Wire.endTransmission();

  delay(2000);
}