#include <Wire.h>

// I2C variables
volatile int mode = 1;  // Mode received from ESP8266 via I2C
int var1 = 1;

void receiveEvent(int bytes) {
  if (Wire1.available() > 0) {
    mode = Wire1.read();  // Read the mode sent by ESP8266
    //Serial.print("Mode received: ");
    Serial.println(mode);
    var1 = mode - 48;
    Serial.println(var1);
  }
}

void setup() {
  Serial.begin(115200);  // Initialize serial communication

  // Wire1.begin();  //SDA & SDL
  Wire1.begin();  //SDA1 & SDL1
  // Wire2.begin();    //SDA2 & SDL2
  Wire.onReceive(receiveEvent);  // Set up receiveEvent to handle incoming data
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire1.beginTransmission(8);  //begin transmit to device 1
  // Wire1.write(byte(0x00));     //send instruction byte
  int val = 47;
  // Wire1.write(val);         //send a value
  Wire1.endTransmission();  //stop transmit
}
