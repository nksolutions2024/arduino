//       W3 ESP32-WROOM
#include <esp_now.h>
#include <WiFi.h>
#include <DHT.h>

// Define GPIO pins and constants for the DHT11 sensor
#define BUILTIN_LED 2    // Built-in LED pin
#define DHT11PIN 4       // DHT11 data pin
#define DHTTYPE DHT11    // Define the sensor type

DHT dht(DHT11PIN, DHTTYPE); // Create an instance of the DHT sensor

// CO2 Sensor Pins and Constants
#define CO2_SENSOR_PIN 34 // Assuming the CO2 sensor is connected to analog pin 34

// Calibration parameters for CO2 sensor
float calibrationFactor = 10.0;
float Ro = 10.0; // Sensor resistance in clean air

// Constants for CO2 mass calculation (assuming standard conditions)
float pressure = 1.0; // Pressure in atm (Standard conditions)
float temperature = 273.15; // Temperature in Kelvin (0°C)
float gasConstant = 0.0821; // Gas constant in L·atm/(mol·K)
float molarMassCO2 = 44.01; // Molar mass of CO2 in g/mol
float airVolume = 1000.0; // Volume of air in liters (adjust as needed)

int sensorValue;
int digitalValue;

// Global variables for storing data
String lastMessage = "No Message"; // Holds the last received ESP-NOW message
float temperatureDHT = NAN;        // Holds the latest temperature reading from DHT11
float humidity = NAN;              // Holds the latest humidity reading from DHT11

// Callback function for ESP-NOW data reception
void onDataRecv(const esp_now_recv_info* recv_info, const uint8_t* data, int dataLen) {
  lastMessage = ""; // Clear the previous message
  for (int i = 0; i < dataLen; i++) {
    lastMessage += (char)data[i];
  }

  // If the received message matches "D1GREEN", "D2GREEN", etc., set corresponding pin HIGH
  if (lastMessage == "D1GREEN") {
    digitalWrite(0, HIGH); // D1 Pin (GPIO 0)
    blinkLED();
  } else if (lastMessage == "D2GREEN") {
    digitalWrite(2, HIGH); // D2 Pin (GPIO 2)
    blinkLED();
  } else if (lastMessage == "D3GREEN") {
    digitalWrite(4, HIGH); // D3 Pin (GPIO 4)
    blinkLED();
  } else if (lastMessage == "D4GREEN") {
    digitalWrite(5, HIGH); // D4 Pin (GPIO 5)
    blinkLED();
  } else if (lastMessage == "D0GREEN") {
    digitalWrite(15, HIGH); // D5 Pin (GPIO 15)
    blinkLED();
  }

  // Debugging output
  Serial.print("Received message: ");
  Serial.println(lastMessage);
}

// Function to blink the built-in LED
void blinkLED() {
  digitalWrite(BUILTIN_LED, HIGH);  // Turn on the LED
  delay(500);                       // Wait for 500ms
  digitalWrite(BUILTIN_LED, LOW);   // Turn off the LED
  delay(500);                       // Wait for 500ms
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Set the built-in LED pin as output
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);

  // Set CO2 sensor pin as input
  pinMode(CO2_SENSOR_PIN, INPUT);

  // Set GPIO pins D1, D2, D3, D4, D0 (D5 pin) as output
  pinMode(0, OUTPUT);  // D1
  pinMode(2, OUTPUT);  // D2
  pinMode(4, OUTPUT);  // D3
  pinMode(5, OUTPUT);  // D4
  pinMode(15, OUTPUT); // D5 (mapped to D0)

  // Initialize Wi-Fi in station mode for ESP32
  WiFi.mode(WIFI_STA);
  Serial.println("Doit Devkit - Combined ESP-NOW, DHT11, and CO2 Program");

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register callback function to handle received data
  esp_now_register_recv_cb(onDataRecv);

  // Initialize DHT11 sensor
  dht.begin();
}

void loop() {
  // Read temperature and humidity from the DHT11 sensor
  temperatureDHT = dht.readTemperature();
  humidity = dht.readHumidity();

  // Create a string with all data
  String output = lastMessage;
  if (isnan(temperatureDHT) || isnan(humidity)) {
    output += ", Temp: Error, Humidity: Error";
  } else {
    output += "," + String(temperatureDHT, 2);
    output += "," + String(humidity, 2);
  }

  // Read CO2 sensor value
  sensorValue = analogRead(CO2_SENSOR_PIN); // Read analog input pin (sensor)
  digitalValue = digitalRead(2);            // Read digital input pin (used for control)

  // Calculate the sensor resistance in clean air (Ro = clean air resistance)
  float sensorResistance = (1023.0 / sensorValue) - 1.0;

  // Estimate CO2 concentration in ppm (based on calibration)
  float co2Concentration = calibrationFactor * sensorResistance / Ro;

  // Calculate carbon emissions (mass of CO2 in grams)
  // Use the ideal gas law to calculate moles of CO2 and then convert to mass
  float co2Moles = (co2Concentration / 1e6) * (pressure * airVolume) / (gasConstant * temperature); // moles of CO2
  float co2Mass = co2Moles * molarMassCO2; // Mass of CO2 in grams

  if (sensorValue > 400) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

  // Combine the CO2 mass into the output string
  output += "," + String(co2Mass, 2);

  // Print the combined string to the Serial Monitor
  Serial.println(output);

  delay(2000); // Wait 2 seconds between readings
}
