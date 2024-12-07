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
// #define FIREBASE_HOST "proj3dec-default-rtdb.firebaseio.com"
// #define FIREBASE_AUTH "R2EjtTTCMeE4C5n02HJmEzKkIygVN4rpbdQRbKOE"
#define FIREBASE_HOST "firewrite5dec-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "JeE7LvGbLvPLldlE3AdnK0wU0lsZRNZZ0lvryUG7"

FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");

  // Initialize Firebase
  firebaseConfig.host = FIREBASE_HOST;
  firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&firebaseConfig, &firebaseAuth);

  Wire.begin();
}

void loop() {
  // Fetch data from Firebase
  if (Firebase.getString(firebaseData, "/arduinos/arduino_1/mode")) {
    if (firebaseData.dataType() == "string") {
      String data = firebaseData.stringData();

      // send data to GIGA(TX1 RX1 Serial2) via UART
      // Serial.println("esp8266-sending-1908");
      Serial.println("Data from Firebase: " + data);
    }
  } else {
    // Serial.println("Error fetching data: " + firebaseData.errorReason());
  }
  // Serial.println("esp8266-Always");

  // // Receiver: Check if there is incoming data from UART
  // if (Serial.available() > 0) {
  //   // Read the incoming data
  //   String receivedData = Serial.readString();

  //   // Print received data to the serial monitor
  //   // Serial.print("Received data: ");  //comment it 
  //   // Serial.println(receivedData);     //comment it as directly sending to Firebase AGENT
  // }

  delay(1000);
}
