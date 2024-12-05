#include <Wire.h>
void setup() {
  Serial.begin(115200);
  Wire.begin(D1, D2);
}

void loop() {
  Wire.requestFrom(8, 10);
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println();
  delay(100);
}