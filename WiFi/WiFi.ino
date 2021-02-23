#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoJson.h>
#include "Credentials.h"

// #define SHOW_LOG

// WiFi settings
#define SSID1 "Bbox-A9482AED"

// Request settings
#define DELAY 300000
#define CONNECT_TIMEOUT 5000
const char *host = "www.instagram.com";
const String param = "/les_coulisses_dune_bethunoise/?__a=1";
const int httpsPort = 443;

ESP8266WiFiMulti wifiMulti;
WiFiClientSecure https;

void setup() {
  #ifdef SHOW_LOG
  Serial.begin(9600);
  #endif
  Serial1.begin(115200);
  
  // Configure WiFi
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  
  // Init WiFi list
  wifiMulti.addAP(SSID1, PASSWORD1);
}
  
void loop() {
  if (wifiMulti.run(CONNECT_TIMEOUT) == WL_CONNECTED) {
    // ESP8266 is connected to a WiFi network
    #ifdef SHOW_LOG
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());
    #endif
    
    String result = getJSONData();
    #ifdef SHOW_LOG
    Serial.println(result);
    #endif
    
    int followers = getFollowersCount(result); // 'followers' may be -1
    #ifdef SHOW_LOG
    Serial.println(followers);
    #endif
    Serial1.println(followers);
    
    delay(DELAY);
  }
  delay(1000);
}
