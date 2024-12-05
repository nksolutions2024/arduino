#include <Wire.h>

void setup() {
  Serial.begin(115200);

  // Initialize I2C communication as Master
  Wire.begin();
}

void loop() {
      String data1 = "other string";
      Serial.println("Data sending to UNO: " + data1);

      // Send data to Arduino Mega via I2C
      Wire.beginTransmission(8);  // Address of the slave (Mega)
      Wire.write("not_variable_data1");          // Send string data
      Wire.endTransmission();

  delay(2000);
}