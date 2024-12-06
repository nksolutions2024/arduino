#include <SPI.h>
#include <Ethernet.h>

// Firebase configuration
#define FIREBASE_HOST "https://traffic-control-system-b1623-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "HXGM54I1SizWeV92XoNzSLnwRudQdenSjpLF7LJ4"

// Ethernet configuration
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Use your own MAC address
IPAddress ip(192, 168, 31, 141); // Use a static IP if necessary

// Firebase data retrieval settings
String mode = "Default";
EthernetClient client;

void setup() {
  Serial.begin(9600);

  // Start Ethernet connection
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip); // Attempt to use static IP if DHCP fails
  }
  delay(1000); // Wait for Ethernet to initialize

  Serial.println("Ethernet shield is connected.");
  Serial.print("Arduino IP Address: ");
  Serial.println(Ethernet.localIP());

  // Connect to Firebase
  if (connectToFirebase()) {
    Serial.println("Connected to Firebase.");
    mode = getFirebaseData(); // Get mode from Firebase
    Serial.print("Mode: ");
    Serial.println(mode);
  } else {
    Serial.println("Failed to connect to Firebase.");
  }
}

void loop() {
  // Code for periodic tasks or data handling
  delay(10000); // Wait for 10 seconds before checking again
}

bool connectToFirebase() {
  // Connect to Firebase by sending GET request for data
  client.connect(FIREBASE_HOST, 80); // Connect to Firebase over HTTP (port 80)
  if (client.connected()) {
    Serial.println("Connected to Firebase server.");
    return true;
  }
  Serial.println("Failed to connect to Firebase server.");
  return false;
}

String getFirebaseData() {
  String response = "";
  
  // Send GET request to Firebase
  client.print("GET /arduinos/arduino_1.json?auth=");
  client.print(FIREBASE_AUTH);
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.println(FIREBASE_HOST);
  client.println("Connection: close");
  client.println();
  
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 20000) { // Increased timeout to 20 seconds
      Serial.println("Timeout, no response from Firebase.");
      return "Timeout"; // Return "Timeout" if no response
    }
  }

  // Read the response from Firebase
  while (client.available()) {
    char c = client.read();
    response += c;
  }

  // Find the mode value in the JSON response (assuming it’s in JSON format)
  int startIndex = response.indexOf("mode\":\"") + 7;
  int endIndex = response.indexOf("\"", startIndex);
  if (startIndex != -1 && endIndex != -1) {
    String modeValue = response.substring(startIndex, endIndex);
    Serial.print("Fetched Mode: ");
    Serial.println(modeValue);
    return modeValue; // Return the fetched mode
  }

  return "Error"; // Return error if no mode value found
}
