#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Replace with your Wi-Fi credentials
//#define WIFI_SSID "TP-Link_68A4"
//#define WIFI_PASSWORD "123456789@POWERX"
// #define WIFI_SSID "Searching..."
// #define WIFI_PASSWORD "Shaikh1234"
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

// Variables for sending data
int L1 = 0;  // Initialize with some value
int L2 = 0;  // Initialize with some value
int L3 = 0;  // Initialize with some value

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
  // Send data to Firebase
  if (Firebase.setInt(firebaseData, "/arduinos/arduino_1/L1", L1)) {//
    Serial.println("L1 value sent: " + String(L1));
  } else {
    Serial.println("Error sending L1: " + firebaseData.errorReason());
  }

  if (Firebase.setInt(firebaseData, "/arduinos/arduino_1/L2", L2)) {
    Serial.println("L2 value sent: " + String(L2));
  } else {
    Serial.println("Error sending L2: " + firebaseData.errorReason());
  }

  if (Firebase.setInt(firebaseData, "/arduinos/arduino_1/L3", L3)) {
    Serial.println("L3 value sent: " + String(L3));
  } else {
    Serial.println("Error sending L3: " + firebaseData.errorReason());
  }

  // Update values of L1, L2, and L3 for the next loop iteration (example logic)
  L1++;
  L2 += 2;
  L3 += 3;

  // Delay before the next update
  delay(2000);
}
