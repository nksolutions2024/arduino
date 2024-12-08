//ambulance Q1 esp8266
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <espnow.h>

// Wi-Fi credentials
#define WIFI_SSID "TP-Link_68A4"
#define WIFI_PASSWORD "123456789@POWERX"

// Firebase credentials
#define FIREBASE_HOST "https://testsih-b8af7-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyDaoJjdLLeGooyJdxgW06ZV4221NQHO14o"

// Define the MAC address of the receiving NodeMCU (NodeMCU 2)
uint8_t nodeMCU2Address[] = { 0x48, 0x3F, 0xDA, 0x7C, 0x82, 0x04 };

// Firebase and Wi-Fi setup
FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

// Define polygons
const float polygon1[][2] = { { 19.8797223, 75.3566141 }, { 19.8797235, 75.3566151 }, { 19.8797237, 75.3566162 }, { 19.8797237, 75.3566163 } };
const float polygon2[][2] = { { 19.8797232, 75.3566193 }, { 19.8797230, 75.3566202 }, { 19.8797229, 75.3566206 }, { 19.8797226, 75.3566201 } };
const float polygon3[][2] = { { 19.8797217, 75.3566222 }, { 19.8797224, 75.3566229 }, { 19.8797224, 75.3566243 }, { 19.8797223, 75.3566253 } };
const float polygon4[][2] = { { 19.8797218, 75.3566251 }, { 19.8797223, 75.356626 }, { 19.8797234, 75.356630 }, { 19.8797236, 75.3566341 } };

int polygon1_points = sizeof(polygon1) / sizeof(polygon1[0]);
int polygon2_points = sizeof(polygon2) / sizeof(polygon2[0]);
int polygon3_points = sizeof(polygon3) / sizeof(polygon3[0]);
int polygon4_points = sizeof(polygon4) / sizeof(polygon4[0]);

// Function to check if point is inside a polygon
bool isPointInPolygon(float x, float y, const float polygon[][2], int n) {
  bool result = false;
  int j = n - 1;
  for (int i = 0; i < n; i++) {
    if (y > polygon[i][1] && y <= polygon[j][1] || y > polygon[j][1] && y <= polygon[i][1]) {
      if (x <= (polygon[i][0] - polygon[j][0]) * (y - polygon[j][1]) / (polygon[i][1] - polygon[j][1]) + polygon[j][0]) {
        result = !result;
      }
    }
    j = i;
  }
  return result;
}

// Callback function to handle status of ESP-NOW send
void onSent(uint8_t* mac_addr, uint8_t sendStatus) {
  Serial.print("Message send status: ");
  if (sendStatus == 0) {
    Serial.println("Delivery Success");
  } else {
    Serial.println("Delivery Failed");
  }
  // Turn off the LED after sending is done
  digitalWrite(LED_BUILTIN, HIGH);  // LED off (inverted logic on ESP8266)
}

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);
  delay(1000);

  // Set WiFi to station mode
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

  // Initialize Firebase
  Firebase.begin(&firebaseConfig, &firebaseAuth);

  // Configure the built-in LED pin
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // Turn LED off initially (inverted logic)

  // Initialize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the send callback to handle status
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);  // Required for ESP8266
  esp_now_register_send_cb(onSent);

  // Register the receiver peer (NodeMCU 2)
  if (esp_now_add_peer(nodeMCU2Address, ESP_NOW_ROLE_SLAVE, 1, NULL, 0) != 0) {
    Serial.println("Failed to add peer");
    return;
  }

  Serial.println("ESP-NOW connection established");
}

void loop() {
  // Read a value from Firebase (example: coordinates)
  if (Firebase.getString(firebaseData, "/")) {
    if (firebaseData.dataType() == "string") {
      String coordinates = firebaseData.stringData();
      // Split the coordinates into latitude and longitude
      float lat = coordinates.substring(0, coordinates.indexOf(',')).toFloat();
      float lon = coordinates.substring(coordinates.indexOf(',') + 1).toFloat();

      String message;

      // Check which polygon the point lies within and create corresponding message
      if (isPointInPolygon(lat, lon, polygon1, polygon1_points)) {
        message = "AMBUARRIVEDa";
      } else if (isPointInPolygon(lat, lon, polygon2, polygon2_points)) {
        message = "AMBUARRIVEDb";
      } else if (isPointInPolygon(lat, lon, polygon3, polygon3_points)) {
        message = "AMBUARRIVEDc";
      } else if (isPointInPolygon(lat, lon, polygon4, polygon4_points)) {
        message = "AMBUARRIVEDd";
      } else {
        message = "AMBUARRIVED";
      }

      // Send the message to NodeMCU 2
      digitalWrite(LED_BUILTIN, LOW);  // Turn LED on (inverted logic)
      if (esp_now_send(nodeMCU2Address, (uint8_t*)message.c_str(), message.length()) == 0) {
        Serial.println("Message sent: " + message);
      } else {
        Serial.println("Error sending message");
      }
    }
  } else {
    Serial.println("Error: " + firebaseData.errorReason());
  }
  delay(2000);
}
