
#include <esp_wifi.h>
#include <esp_now.h>
#include <WiFi.h>
#include "config.h"

char kbinp;
//CC:DB:A7:33:5A:00
uint8_t broadcastAddress[] = RECEIVER_MAC;

typedef struct Directions {
  bool fwd;
  bool bck;
  bool lft;
  bool rgt;
} Directions;

Directions direction;

esp_now_peer_info_t peerInfo;

void OnDataSent(const esp_now_send_info_t *tx_info, esp_now_send_status_t status) {
  //Serial.print("\r\nLast Packet Send Status:\t");
  //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  WiFi.mode(WIFI_STA);
  esp_wifi_set_ps(WIFI_PS_NONE);
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);
  Serial.begin(115200);
  pinMode(32,OUTPUT);
  pinMode(33,OUTPUT);
  pinMode(27,OUTPUT);
  pinMode(26,OUTPUT);

  if (esp_now_init() != ESP_OK) {
    //Serial.println("Error initializing ESP-NOW");
  }

 
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    //Serial.println("Failed to add peer");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
}

void loop() {
  if (Serial.available() > 0) {
    kbinp = Serial.read();
    //Serial.print("Received key: ");
    //Serial.println(kbinp);
  }
  
  if (kbinp == 'w') {
    direction.fwd = 1;
  }
  if (kbinp == 's') {
    direction.bck = 1;
  }
  if (kbinp == 'a') {
    direction.lft = 1;
  }
  if (kbinp == 'd') {
    direction.rgt = 1;
  }
    if (kbinp == '}') {
    direction.fwd = 0;
  }
  if (kbinp == 'y') {
    direction.bck = 0;
  }
  if (kbinp == 'g') {
    direction.lft = 0;
  }
  if (kbinp == 'j') {
    direction.rgt = 0;
  }
  digitalWrite(32,direction.fwd);
  digitalWrite(33,direction.bck);
  digitalWrite(27,direction.lft);
  digitalWrite(26,direction.rgt);

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &direction, sizeof(direction));
   
  if (result == ESP_OK) {
    //Serial.println("Sent with success");
  }
  else {
    //Serial.println("Error sending the data");
  }

}
