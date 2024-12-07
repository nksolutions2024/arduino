#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin();  //SDA & SDL
  // Wire1.begin();  //SDA1 & SDL1
  // Wire2.begin();    //SDA2 & SDL2
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(8);  //begin transmit to device 1
  // Wire.write(byte(0x00));     //send instruction byte
  int val = 47;
  Wire.write(val);            //send a value
  Wire.endTransmission();     //stop transmit
}
