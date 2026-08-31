#include <utility>
#include <cmath>
#include <esp_wifi.h>
#include <esp_now.h>
#include <WiFi.h>

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

int inverse_top(float x, float y){
  float tan_value = y/x;
  return(atan(tan_value)*(180/numbers::pi));
}

pair<float,float> inverse_side(float x, float y, float a, float b){
  float c = sqrt(pow(x,2)+pow(y,2));
  float angle_a_c = acos((pow(a,2)-pow(b,2)+pow(c,2))/(2*c*a))*(180/numbers::pi);//compare to the middle one and use -90 - 90
  float angle_a_b = acos((pow(a,2)-pow(c,2)+pow(b,2))/(2*a*b))*(180/numbers::pi);//use value 0 - 180 na krub ee
  float angle_c_horizon = atan(y/c)*(180/numbers::pi);
  float angle_a_horizon = angle_a_b+angle_c_horizon;
  return make_pair(angle_a_horizon,angle_a_c);
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
