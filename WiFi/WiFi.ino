#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoJson.h>
#include "Credentials.h"

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
  Serial.begin(9600);
  
  // Configure WiFi
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  
  // Init WiFi list
  wifiMulti.addAP(SSID1, PASSWORD1);
}

void loop() {
  if (wifiMulti.run(CONNECT_TIMEOUT) == WL_CONNECTED) {
    // ESP8266 is connected to a WiFi network
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());
    
    String result = getJSONData();
    Serial.println(result);
    
    int followers = getFollowersCount(result); // 'followers' may be -1
    Serial.println(followers);
    
    delay(DELAY);
  }
  delay(1000);
}
