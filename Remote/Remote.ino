#include "ESP32_NOW.h"
#include "WiFi.h"
#include <esp_mac.h> 

#define ESPNOW_WIFI_CHANNEL 6

const int freq = 5000;
const int resolution = 8;

int joyXpin = 34;
int joyYpin = 35;
int buttonPin = 32;

int xVal;
int yVal;
int buttonState;

// Struct to hold joystick data
typedef struct struct_message {
  int xVal;
  int yVal;
  int buttonState;
} struct_message;

struct_message joyData;

class ESP_NOW_Broadcast_Peer : public ESP_NOW_Peer {
public:
  ESP_NOW_Broadcast_Peer(uint8_t channel, wifi_interface_t iface, const uint8_t *lmk) 
    : ESP_NOW_Peer(ESP_NOW.BROADCAST_ADDR, channel, iface, lmk) {}

  ~ESP_NOW_Broadcast_Peer() {
    remove();
  }

  bool begin() {
    if (!ESP_NOW.begin() || !add()) {
      log_e("Failed to initialize ESP-NOW or register the broadcast peer");
      return false;
    }
    return true;
  }

  bool send_message(const uint8_t *data, size_t len) {
    if (!send(data, len)) {
      log_e("Failed to broadcast message");
      return false;
    }
    return true;
  }
};

ESP_NOW_Broadcast_Peer broadcast_peer(ESPNOW_WIFI_CHANNEL, WIFI_IF_STA, NULL);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.setChannel(ESPNOW_WIFI_CHANNEL);

  pinMode(joyXpin, INPUT);
  pinMode(joyYpin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  if (!broadcast_peer.begin()) {
    Serial.println("Failed to initialize broadcast peer");
    delay(5000);
    ESP.restart();
  }

  Serial.println("Setup complete.");
}

void loop() {
  // Read joystick values
  joyData.xVal = analogRead(joyXpin);
  joyData.yVal = analogRead(joyYpin);
  joyData.buttonState = digitalRead(buttonPin);

  // Send joystick data via ESP-NOW
  if (!broadcast_peer.send_message((uint8_t *)&joyData, sizeof(joyData))) {
    Serial.println("Failed to broadcast joystick data");
  }

  delay(100);  // Send data every 100ms
}
