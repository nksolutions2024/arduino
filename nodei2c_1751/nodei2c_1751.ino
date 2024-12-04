#include <Wire.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Replace with your Wi-Fi credentials
// #define WIFI_SSID "TP-Link_68A4"
// #define WIFI_PASSWORD "123456789@POWERX"
#define WIFI_SSID "deep"
#define WIFI_PASSWORD "12345678"

// Firebase credentials
// #define FIREBASE_HOST "control-60b4a-default-rtdb.firebaseio.com"
// #define FIREBASE_AUTH "bTcrTo4dGQlUYwzQmPv0H3xARHKWNDUgT8Mqqkbc"
#define FIREBASE_HOST "proj3dec-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "R2EjtTTCMeE4C5n02HJmEzKkIygVN4rpbdQRbKOE"

FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");

  // Initialize Firebase
  firebaseConfig.host = FIREBASE_HOST;
  firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&firebaseConfig, &firebaseAuth);

  // Initialize I2C communication as Master
  Wire.begin();
}

void loop() {
  // Fetch data from Firebase
  if (Firebase.getString(firebaseData, "/arduinos/arduino_1/mode")) {
    if (firebaseData.dataType() == "string") {
      String data = firebaseData.stringData();
      Serial.println("Data from Firebase: " + data);

      // Send data to Arduino Mega via I2C
      Wire.beginTransmission(8); // Address of the slave (Mega)
      Wire.write(data.c_str());  // Send string data
      Wire.endTransmission();
    }
  } else {
    Serial.println("Error fetching data: " + firebaseData.errorReason());
  }
  delay(2000);
}
