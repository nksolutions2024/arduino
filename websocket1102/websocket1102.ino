#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>

// WiFi credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

// WebSocket server on port 81
WebSocketsServer webSocket = WebSocketsServer(81);

// Pin configuration
const int ledPin = D1; // LED connected to pin D1
bool ledState = false;

void setup() {
  // Initialize serial monitor
  Serial.begin(115200);

  // Initialize LED pin
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Start WebSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  Serial.println("WebSocket server started!");
}

void loop() {
  // Handle WebSocket communication
  webSocket.loop();
}

// WebSocket event handler
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;

    case WStype_CONNECTED:
      Serial.printf("[%u] Connected from %s\n", num, webSocket.remoteIP(num).toString().c_str());
      webSocket.sendTXT(num, "Welcome to ESP8266 WebSocket!");
      break;

    case WStype_TEXT:
      Serial.printf("[%u] Received: %s\n", num, payload);

      // Toggle LED on "toggle" command
      if (strcmp((const char*)payload, "toggle") == 0) {
        ledState = !ledState;
        digitalWrite(ledPin, ledState ? HIGH : LOW);
        webSocket.sendTXT(num, ledState ? "LED is ON" : "LED is OFF");
      }
      break;

    default:
      break;
  }
}
