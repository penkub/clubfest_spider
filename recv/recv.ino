#include <utility>
#include <esp_wifi.h>
#include <esp_now.h>
#include <WiFi.h>
#include "ik.cpp"

using namespace std;

const float thigh = 1;
const float foot = 1;

const float thigh_angle = 0;
const float foot_angle = 0;

typedef struct Directions {
  bool fwd;
  bool bck;
  bool lft;
  bool rgt;
} Directions;

Directions direction;

void dataRecv(const esp_now_recv_info_t *esp_now_info, const uint8_t * data, int dirSize){
  memcpy(&direction, data, dirSize);
  digitalWrite(32,direction.fwd);
  digitalWrite(33,direction.bck);
  digitalWrite(27,direction.lft);
  digitalWrite(26,direction.rgt);
}

void setup() {
  Serial.begin(115200);
  pinMode(32,OUTPUT);
  pinMode(33,OUTPUT);
  pinMode(27,OUTPUT);
  pinMode(26,OUTPUT);

  WiFi.mode(WIFI_STA);
  esp_wifi_set_ps(WIFI_PS_NONE);
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);
  if (esp_now_init() != ESP_OK) {
    ////////////Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(dataRecv);
}

void loop() {
}
