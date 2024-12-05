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
    Serial.print("LED1: ");
    Serial.println(status );
  }

  // String data1 = "other string";
  // Serial.println("Data sending to UNO: 1657 " + data1);

  // Send data to Arduino Mega via I2C
  // Wire.beginTransmission(8);         // Address of the slave (Mega)
  // Wire.write("1656directly_written");  // Send string data
  // Wire.endTransmission();

  delay(2000);
}