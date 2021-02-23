const char *host = "www.instagram.com";
const String param = "/les_coulisses_dune_bethunoise/?__a=1";
const int httpsPort = 443;

String getJSONData(){
  #ifdef SHOW_LOG
  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  #endif
  https.setFingerprint(fingerprint);
  https.setTimeout(15000);
  delay(1000);

  #ifdef SHOW_LOG
  Serial.print("HTTPS Connecting");
  #endif
  int r = 0;
  while((!https.connect(host, httpsPort)) && (r < 30)){
      delay(100);
      #ifdef SHOW_LOG
      Serial.print(".");
      #endif
      r++;
  }
  #ifdef SHOW_LOG
  if(r == 30) Serial.println("\nConnection failed");
  else Serial.println("\nConnected to web");
  #endif

  #ifdef SHOW_LOG
  Serial.print("requesting URL: ");
  Serial.println(host+param);
  #endif
  https.print(String("GET ") + param + " HTTP/1.0\r\n" +
               "Host: " + host + "\r\n" +               
               "Connection: close\r\n" +
               "Cookie: " + api + "\r\n\r\n");
  #ifdef SHOW_LOG
  Serial.println("request sent");
  #endif
                  
  while (https.connected()) {
    String line = https.readStringUntil('\n');
    if (line == "\r") {
      #ifdef SHOW_LOG
      Serial.println("headers received");
      #endif
      break;
    }
  }

  String res = "";
  int i = 0;
  int l = 0;
  while(https.available()){
    char c = https.read();
    //Serial.write(c);
    res.concat(c);
    i++;
    if(i > 70){
      l++;
      //Serial.print(" - ");
      //Serial.println(l);
      i = 0;
    }
    if(c == '\n') break;
  }

  #ifdef SHOW_LOG
  Serial.println("closing connection");
  #endif
  https.stop();

  int idx = res.indexOf("edge_followed_by") + 18;
  bool end_obj = false;
  String result = "";
  while(!end_obj){
    String c = res.substring(idx, idx+1);
    result.concat(c);
    idx++;
    end_obj = c == "}";
  }

  return result;
}

int getFollowersCount(String jsondata){
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, jsondata);
  if (error) {
    #ifdef SHOW_LOG
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    #endif
    return -1;
  }
  return doc["count"];
}
