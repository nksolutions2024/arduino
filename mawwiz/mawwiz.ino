#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Replace with your Wi-Fi credentials
// #define WIFI_SSID "TP-Link_68A4"
// #define WIFI_PASSWORD "123456789@POWERX"
#define WIFI_SSID "deep"
#define WIFI_PASSWORD "12345678"



// Define Firebase credentials
#define FIREBASE_HOST "proj3dec-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "R2EjtTTCMeE4C5n02HJmEzKkIygVN4rpbdQRbKOE"
// #define FIREBASE_HOST "control-60b4a-default-rtdb.firebaseio.com"
// #define FIREBASE_AUTH "bTcrTo4dGQlUYwzQmPv0H3xARHKWNDUgT8Mqqkbc"
FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);
  delay(1000);

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");

  // Configure Firebase
  firebaseConfig.host = FIREBASE_HOST;
  firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;

  // Optional: Set the maximum timeout for Firebase operations
  firebaseConfig.timeout.socketConnection = 10000;

  // Initialize Firebase
  Firebase.begin(&firebaseConfig, &firebaseAuth);
}

void loop() {
  // Read a value from Firebase
  if (Firebase.getString(firebaseData, "/arduinos/arduino_1/mode")) {
    if (firebaseData.dataType() == "string") {
      Serial.println(firebaseData.stringData());
    }
  } else {
    Serial.println("Error: " + firebaseData.errorReason());
  }
  delay(2000);
}
