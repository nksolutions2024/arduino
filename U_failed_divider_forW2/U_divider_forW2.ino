//divider
#include <espnow.h>
#include <ESP8266WiFi.h>

// MAC address of the peer device
uint8_t peerAddress[] = {0x94, 0x54, 0xC5, 0xE9, 0x03, 0xDC};

// Built-in LED pin
const int ledPin = LED_BUILTIN;

// Callback function to handle received data
void onDataRecv(uint8_t *macAddr, uint8_t *data, uint8_t dataLen) {
  // Blink LED to indicate data reception
  digitalWrite(ledPin, LOW); // Turn on the LED
  delay(100);               // Delay for visibility
  digitalWrite(ledPin, HIGH); // Turn off the LED

  Serial.print("Received message: ");
  String incomingData = "";
  for (int i = 0; i < dataLen; i++) {
    incomingData += (char)data[i];
  }
  Serial.println(incomingData);

  if (incomingData == "AMBUARRIVEDa") {
    // Send "D1GREEN" to the peer device
    const char *response = "D1GREEN";
    if (esp_now_send(peerAddress, (uint8_t *)response, strlen(response)) == 0) {
      Serial.println("Message sent: D1GREEN");
    } else {
      Serial.println("Error sending message");
    }
  } else if (incomingData == "AMBUARRIVEDb") {
    // Send "D2GREEN" to the peer device
    const char *response = "D2GREEN";
    if (esp_now_send(peerAddress, (uint8_t *)response, strlen(response)) == 0) {
      Serial.println("Message sent: D2GREEN");
    } else {
      Serial.println("Error sending message");
    }
  } else if (incomingData == "AMBUARRIVEDc") {
    // Send "D3GREEN" to the peer device
    const char *response = "D3GREEN";
    if (esp_now_send(peerAddress, (uint8_t *)response, strlen(response)) == 0) {
      Serial.println("Message sent: D3GREEN");
    } else {
      Serial.println("Error sending message");
    }
  } else if (incomingData == "AMBUARRIVEDd") {
    // Send "D4GREEN" to the peer device
    const char *response = "D4GREEN";
    if (esp_now_send(peerAddress, (uint8_t *)response, strlen(response)) == 0) {
      Serial.println("Message sent: D4GREEN");
    } else {
      Serial.println("Error sending message");
    }
  } else if (incomingData == "AMBUARRIVED") {
    // Send "D0GREEN" to the peer device for NA
    const char *response = "D0GREEN";
    if (esp_now_send(peerAddress, (uint8_t *)response, strlen(response)) == 0) {
      Serial.println("Message sent: D0GREEN");
    } else {
      Serial.println("Error sending message");
    }
  }
}

// Callback function to handle send status
void onSent(uint8_t *macAddr, uint8_t sendStatus) {
  // Blink LED to indicate data sent
  digitalWrite(ledPin, LOW); // Turn on the LED
  delay(100);               // Delay for visibility
  digitalWrite(ledPin, HIGH); // Turn off the LED

  Serial.print("Send status: ");
  if (sendStatus == 0) {
    Serial.println("Delivery Success");
  } else {
    Serial.println("Delivery Failed");
  }
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Configure built-in LED pin
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // Turn off the LED initially

  // Initialize WiFi in station mode
  WiFi.mode(WIFI_STA);
  Serial.println("ESP-NOW Receiver & Sender");

  // Initialize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register callback functions
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO); // Set as both sender and receiver
  esp_now_register_recv_cb(onDataRecv);
  esp_now_register_send_cb(onSent);

  // Add peer
  if (esp_now_add_peer(peerAddress, ESP_NOW_ROLE_COMBO, 0, NULL, 0) != 0) {
    Serial.println("Failed to add peer");
    return;
  }

  Serial.println("ESP-NOW connection established");
}

void loop() {
  // Nothing to do here, everything is handled in the callbacks
}

