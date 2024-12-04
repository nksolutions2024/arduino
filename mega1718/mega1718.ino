#include <Wire.h>

// Define analog pins for emergency vehicle detection
const int sensorPins[4] = {A1, A2, A3, A4};
const int countdownReductionPin = A0; // Define A0 for countdown reduction

// Define signal timings
int timers[4] = {20, 20, 20, 20}; // Timer for each lane (in seconds)
int yellowTime = 2;               // Duration for yellow light (in seconds)
int currentTimer = 20;            // Current timer for the active lane
int activeLane = 0;               // Index of the active lane
bool emergencyMode = false;
bool yellowMode = false;          // Indicates if yellow light is active
unsigned long yellowStartTime = 0;
unsigned long emergencyPauseTime = 0;
int previousLane = -1;            // Lane that was active before emergency

// Lane names for readability
const char* laneNames[4] = {"Up Lane (A1)", "Right Lane (A2)", "Down Lane (A3)", "Left Lane (A4)"};

// Time tracking
unsigned long lastUpdateTime = 0;

// I2C variables
volatile int mode = 1; // Mode received from ESP8266 via I2C
int var1 = 1;

// 7-segment display pins
const int segPins[7] = {2, 3, 4, 5, 6, 7, 8}; // Segment pins A-G
const int digitPins[4] = {9, 10, 11, 12};     // Control pins for the 4 digits

// LED pins for traffic lights
const int upLaneLEDs[3] = {22, 24, 26};    // RED, YELLOW, GREEN
const int downLaneLEDs[3] = {23, 25, 27};  // RED, YELLOW, GREEN
const int leftLaneLEDs[3] = {48, 50, 52};  // RED, YELLOW, GREEN
const int rightLaneLEDs[3] = {49, 51, 53}; // RED, YELLOW, GREEN

// Lane transition pins
const int laneTransitionPins[4] = {14, 15, 16, 17}; // Up, Right, Down, Left

// I2C receive function
void receiveEvent(int bytes) {
  if (Wire.available() > 0) {
    mode = Wire.read(); // Read the mode sent by ESP8266
    //Serial.print("Mode received: ");
    Serial.println(mode);
    var1 = mode-48;
    Serial.println(var1);
  }
}

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  
  // Initialize I2C communication
  Wire.begin(8); // Arduino acts as I2C slave with address 8
  Wire.onReceive(receiveEvent); // Set up receiveEvent to handle incoming data

  // Initialize segment pins as outputs
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }

  // Initialize digit control pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], HIGH); // Turn off all digits initially
  }

  // Initialize LED pins as outputs
  for (int i = 0; i < 3; i++) {
    pinMode(upLaneLEDs[i], OUTPUT);
    pinMode(downLaneLEDs[i], OUTPUT);
    pinMode(leftLaneLEDs[i], OUTPUT);
    pinMode(rightLaneLEDs[i], OUTPUT);
  }

  // Initialize lane transition pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(laneTransitionPins[i], OUTPUT);
    digitalWrite(laneTransitionPins[i], LOW); // Turn off all lane transition pins initially
  }

  // Set the first lane to start
  activeLane = 0;
  currentTimer = timers[activeLane];
  printSignalStatus();
}

void loop() {
  // Check mode and execute the corresponding logic
  switch (var1) {
    case 1:
      // Normal operation and emergency handling
      handleNormalAndEmergency();
      break;

    case 2:
      // Placeholder for Mode 2 logic
      Serial.println("Mode 2 is not yet implemented.");
      delay(1000);
      break;

    case 3:
      // Placeholder for Mode 3 logic
      Serial.println("Mode 3 is not yet implemented.");
      delay(1000);
      break;

    case 4:
      // Placeholder for Mode 4 logic
      Serial.println("Mode 4 is not yet implemented.");
      delay(1000);
      break;

    default:
      // Handle invalid modes
      Serial.println("Invalid mode selected. Please select a valid mode.");
      delay(1000);
      break;
  }
}

void handleNormalAndEmergency() {
  // Check for emergency vehicles and normal countdown logic
  bool emergencyDetected = false;
  int emergencyLane = -1;
  for (int i = 0; i < 4; i++) {
    if (analogRead(sensorPins[i]) > 1000) {
      emergencyDetected = true;
      emergencyLane = i;
      break;
    }
  }

  if (emergencyDetected) {
    if (!emergencyMode) {
      previousLane = activeLane;
      emergencyPauseTime = currentTimer;
      emergencyMode = true;
    }
    handleEmergency(emergencyLane);
  } else {
    if (emergencyMode) {
      emergencyMode = false;
      activeLane = previousLane;
      currentTimer = emergencyPauseTime;
      printSignalStatus();
    }
    normalOperation();
  }
}

void normalOperation() {
  // Normal traffic light operation logic
  if (yellowMode) {
    if (millis() - yellowStartTime >= yellowTime * 1000) {
      yellowMode = false;
      activeLane = (activeLane + 1) % 4;
      currentTimer = timers[activeLane];
      printSignalStatus();
    }
  } else {
    if (millis() - lastUpdateTime >= 1000) {
      lastUpdateTime = millis();
      if (currentTimer > 0) {
        currentTimer--;
      }
      if (currentTimer <= 0) {
        yellowMode = true;
        yellowStartTime = millis();
        setTrafficLights(activeLane, LOW, HIGH);
        Serial.println("\n--- Yellow Mode Activated ---");
        Serial.print(laneNames[activeLane]);
        Serial.println(": Yellow (Transition to Red)");
      }
    }
  }
}

void handleEmergency(int emergencyLane) {
  // Emergency handling logic
  Serial.println("\n--- Emergency Mode Activated ---");
  setTrafficLights(emergencyLane, HIGH, LOW);
  for (int i = 0; i < 4; i++) {
    if (i != emergencyLane) {
      setTrafficLights(i, LOW, LOW);
    }
  }

  if (analogRead(sensorPins[emergencyLane]) <= 1000) {
    emergencyMode = false;
    activeLane = previousLane;
    currentTimer = emergencyPauseTime;
    printSignalStatus();
  }
}

void printSignalStatus() {
  // Print signal status to Serial
  Serial.println("\n--- Signal Status Update ---");
  Serial.print(laneNames[activeLane]);
  Serial.println(": Green");
  setTrafficLights(activeLane, HIGH, LOW);
  for (int i = 0; i < 4; i++) {
    if (i != activeLane) {
      Serial.print(laneNames[i]);
      Serial.println(": Red");
      setTrafficLights(i, LOW, LOW);
    }
  }
}

void setTrafficLights(int lane, bool greenState, bool yellowState) {
  // Set traffic light states
  switch (lane) {
    case 0:
      digitalWrite(upLaneLEDs[0], !greenState);
      digitalWrite(upLaneLEDs[1], yellowState);
      digitalWrite(upLaneLEDs[2], greenState);
      break;
    case 1:
      digitalWrite(rightLaneLEDs[0], !greenState);
      digitalWrite(rightLaneLEDs[1], yellowState);
      digitalWrite(rightLaneLEDs[2], greenState);
      break;
    case 2:
      digitalWrite(downLaneLEDs[0], !greenState);
      digitalWrite(downLaneLEDs[1], yellowState);
      digitalWrite(downLaneLEDs[2], greenState);
      break;
    case 3:
      digitalWrite(leftLaneLEDs[0], !greenState);
      digitalWrite(leftLaneLEDs[1], yellowState);
      digitalWrite(leftLaneLEDs[2], greenState);
      break;
  }
}
