#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "proj3dec-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "R2EjtTTCMeE4C5n02HJmEzKkIygVN4rpbdQRbKOE"

const char* ssid = "deep";
const char* password = "12345678";

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  if (Firebase.getString(firebaseData, "message")) {
    if (firebaseData.dataType() == "string") {
      Serial.println(firebaseData.stringData());
    }
  } else {
    Serial.println("Failed to read data: " + firebaseData.errorReason());
  }
  delay(2000);  // Adjust the delay as needed
}
