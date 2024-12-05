
#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  // Wire.begin(0,2);
  Serial.begin(9600);  // start serial for output
  delay(100);
  Serial.print("Master Ready");
}

void loop() {
  Wire.requestFrom(8, 6);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }

  delay(500);
}