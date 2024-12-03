#include <ESP8266WiFi.h>
#include<FirebaseESP8266.h>
// Set these to run example.
#define FIREBASE_HOST "proj3dec.firebaseio.com"
#define FIREBASE_AUTH "R2EjtTTCMeE4C5n02HJmEzKkIygVN4rpbdQRbKOE"
#define WIFI_SSID "deep"
#define WIFI_PASSWORD "12345678"

FirebaseData firebaseData;

void setup() {
  Serial.begin(9600);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;

void loop() {
  }
