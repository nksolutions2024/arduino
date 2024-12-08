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

// Variables for sending data
int L1 = 0;
int L2 = 0;
int L3 = 0;

void setup() {
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
  // Optional: Set the maximum timeout for Firebase operations
  firebaseConfig.timeout.socketConnection = 10000;
  // Initialize Firebase
  Firebase.begin(&firebaseConfig, &firebaseAuth);
}

void loop() {
  // Serial.println("esp8266-Always");

  // Fetch data from Firebase
  if (Firebase.getString(firebaseData, "/arduinos/arduino_1/mode")) {
    if (firebaseData.dataType() == "string") {
      String data = firebaseData.stringData();

      // send data to GIGA(TX1 RX1 Serial2) via UART
      // Serial.println("Data from Firebase: " + data); //debugging_point1
    }
  } else {
    // Serial.println("Error fetching data: " + firebaseData.errorReason());
  }

  // // COMMENT BELOW 9 LINES (Receiver code)
  // if (Serial.available() > 0) {
  //   // Read the incoming data
  //   String receivedData = Serial.readString();

  //   // Print received data to the serial monitor
  //   Serial.print("Received data: ");  //comment it
  //   Serial.println(receivedData);     //comment it as directly sending to Firebase AGENT
  // }

  // Send data to Firebase
  if (Firebase.setInt(firebaseData, "/arduinos/arduino_1/L1", L1)) {
    Serial.print(""); //working properly yes it is blank
  }
  // else {
  //   // Serial.println("Error sending L1: " + firebaseData.errorReason());
  // }

  L1 = L1 + 4;

  //giga_counter
  int g_counter=14;
  Serial.println(g_counter); //working OK OK OK

  delay(1000);
}