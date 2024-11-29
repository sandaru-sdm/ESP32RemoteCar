#include <esp_now.h>
#include <WiFi.h>
#include <esp_mac.h>

#define ESPNOW_WIFI_CHANNEL 6

// Struct to hold received joystick data
typedef struct struct_message {
  int xVal;
  int yVal;
  int buttonState;
} struct_message;

struct_message joyData;

const int freq = 5000;
const int resolution = 8;
int ENApin = 4;
int IN1Pin = 16;
int IN2Pin = 17;
int IN3Pin = 5;
int IN4Pin = 18;
int ENBpin = 19;
int buzzerPin = 2;

void setupMotorPins() {
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT);
  pinMode(IN3Pin, OUTPUT);
  pinMode(IN4Pin, OUTPUT);

  ledcAttach(ENApin,  freq,  resolution);
  ledcAttach(ENBpin,  freq,  resolution);

  pinMode(buzzerPin, OUTPUT);
}

void carForward() {
  int motorSpeed = map(joyData.yVal, 2500, 0, 70, 255);
  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, HIGH);
  digitalWrite(IN4Pin, LOW);
  ledcWrite(0, motorSpeed);
  ledcWrite(1, motorSpeed);
}

void carBackward() {
  int motorSpeed = map(joyData.yVal, 2800, 4095, 70, 255);
  digitalWrite(IN1Pin, LOW);
  digitalWrite(IN2Pin, HIGH);
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, HIGH);
  ledcWrite(0, motorSpeed);
  ledcWrite(1, motorSpeed);
}

void carTurnRight() {
  int motorSpeed = map(joyData.xVal, 3000, 4095, 70, 150);
  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, LOW);
  ledcWrite(0, motorSpeed);
  ledcWrite(1, 0);
}

void carTurnLeft() {
  int motorSpeed = map(joyData.xVal, 2000, 0, 70, 150);
  digitalWrite(IN1Pin, LOW);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, HIGH);
  digitalWrite(IN4Pin, LOW);
  ledcWrite(0, 0);
  ledcWrite(1, motorSpeed);
}

void deadZone() {
  digitalWrite(IN1Pin, LOW);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, LOW);
  ledcWrite(0, 0);
  ledcWrite(1, 0);
}

// ESP-NOW callback function when data is received
void onDataRecv(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
  memcpy(&joyData, incomingData, sizeof(joyData));

  // Control car based on joystick data
  if (joyData.yVal < 2000) {
    carForward();
  } else if (joyData.yVal == 4095 && joyData.xVal == 4095) {
    carBackward();
  } else if (joyData.xVal < 2000) {
    carTurnLeft();
  } else if (joyData.xVal == 4095 && (joyData.yVal < 4000 && joyData.yVal > 3000)) {
    carTurnRight();
  } else if ((joyData.yVal >= 2000 && joyData.yVal <= 3000) || (joyData.xVal >= 2000 && joyData.xVal <= 3000)) {
    deadZone();
  }

  if (joyData.buttonState == HIGH) {
    digitalWrite(buzzerPin, LOW);
  } else {
    digitalWrite(buzzerPin, HIGH);
  }
}

void setup() {
  Serial.begin(115200);

  // Initialize WiFi in Station mode
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Initialize motor pins
  setupMotorPins();

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register callback for received data
  esp_now_register_recv_cb(onDataRecv);

  Serial.println("Setup complete. Waiting for joystick data...");
}

void loop() {
  delay(1000);
}
