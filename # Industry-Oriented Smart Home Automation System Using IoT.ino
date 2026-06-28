
#ifdef ENABLE_DEBUG
#define DEBUG_ESP_PORT Serial
#define NODEBUG_WEBSOCKETS
#define NDEBUG
#endif

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <map>
#include "SinricPro.h"
#include "SinricProSwitch.h"

#define WIFI_SSID "Home_WiFi"
#define WIFI_PASS "Password@123"

#define APP_KEY "a1b2c3d4e5f60718293a4b5c6d7e8f90"
#define APP_SECRET "7f4c2e91-8d53-4b6a-a2f7-91c5e3d8b6a4"

#define DEVICE_ID_1 "64b3f4a8c2d1457e91ab23cd"
#define DEVICE_ID_2 "64b3f4a8c2d1457e91ab23ce"
#define DEVICE_ID_3 "64b3f4a8c2d1457e91ab23cf"
#define DEVICE_ID_4 "64b3f4a8c2d1457e91ab23d0"

#define RelayPin1 D1
#define RelayPin2 D2
#define RelayPin3 D5
#define RelayPin4 D6
#define SwitchPin1 D7
#define SwitchPin2 D3
#define SwitchPin3 D4
#define SwitchPin4 RX
#define wifiLed LED_BUILTIN
#define BAUD_RATE 9600
#define DEBOUNCE_TIME 250
#define TACTILE_BUTTON

struct DeviceConfig { int relayPIN; int flipSwitchPIN; };
std::map<String, DeviceConfig> devices = {
 {DEVICE_ID_1,{RelayPin1,SwitchPin1}},
 {DEVICE_ID_2,{RelayPin2,SwitchPin2}},
 {DEVICE_ID_3,{RelayPin3,SwitchPin3}},
 {DEVICE_ID_4,{RelayPin4,SwitchPin4}}
};

struct FlipSwitchConfig {
  String deviceId;
  bool lastFlipSwitchState;
  unsigned long lastFlipSwitchChange;
};

std::map<int, FlipSwitchConfig> flipSwitches;

void setupRelays(){
  for(auto &d:devices){ pinMode(d.second.relayPIN,OUTPUT); digitalWrite(d.second.relayPIN,HIGH); }
}

void setupFlipSwitches(){
  for(auto &d:devices){
    FlipSwitchConfig c;
    c.deviceId=d.first; c.lastFlipSwitchState=HIGH; c.lastFlipSwitchChange=0;
    flipSwitches[d.second.flipSwitchPIN]=c;
    pinMode(d.second.flipSwitchPIN,INPUT_PULLUP);
  }
}

bool onPowerState(String deviceId,bool &state){
  Serial.printf("%s: %s\n",deviceId.c_str(),state?"ON":"OFF");
  digitalWrite(devices[deviceId].relayPIN,!state);
  return true;
}

void handleFlipSwitches(){
  unsigned long now=millis();
  for(auto &fs:flipSwitches){
    if(now-fs.second.lastFlipSwitchChange>DEBOUNCE_TIME){
      bool s=digitalRead(fs.first);
      if(s!=fs.second.lastFlipSwitchState){
#ifdef TACTILE_BUTTON
        if(s){
#endif
          fs.second.lastFlipSwitchChange=now;
          String id=fs.second.deviceId;
          int relay=devices[id].relayPIN;
          bool newState=!digitalRead(relay);
          digitalWrite(relay,newState);
          SinricProSwitch &sw=SinricPro[id];
          sw.sendPowerStateEvent(!newState);
#ifdef TACTILE_BUTTON
        }
#endif
        fs.second.lastFlipSwitchState=s;
      }
    }
  }
}

void setupWiFi(){
  Serial.print("Connecting");
  WiFi.begin(WIFI_SSID,WIFI_PASS);
  while(WiFi.status()!=WL_CONNECTED){ delay(500); Serial.print(".");}
  digitalWrite(wifiLed,LOW);
  Serial.println("\nConnected");
  Serial.println(WiFi.localIP());
}

void setupSinricPro(){
  for(auto &d:devices){
    SinricProSwitch &sw=SinricPro[d.first];
    sw.onPowerState(onPowerState);
  }
  SinricPro.begin(APP_KEY,APP_SECRET);
  SinricPro.restoreDeviceStates(true);
}

void setup(){
  Serial.begin(BAUD_RATE);
  pinMode(wifiLed,OUTPUT);
  digitalWrite(wifiLed,HIGH);
  setupRelays();
  setupFlipSwitches();
  setupWiFi();
  setupSinricPro();
}

void loop(){
  SinricPro.handle();
  handleFlipSwitches();
}
