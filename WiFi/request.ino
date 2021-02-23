String getJSONData(){
  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  https.setFingerprint(fingerprint);
  https.setTimeout(15000);
  delay(1000);
  
  Serial.print("HTTPS Connecting");
  int r = 0;
  while((!https.connect(host, httpsPort)) && (r < 30)){
      delay(100);
      Serial.print(".");
      r++;
  }
  if(r == 30) Serial.println("\nConnection failed");
  else Serial.println("\nConnected to web");
  
  Serial.print("requesting URL: ");
  Serial.println(host+param);
  https.print(String("GET ") + param + " HTTP/1.0\r\n" +
               "Host: " + host + "\r\n" +               
               "Connection: close\r\n" +
               "Cookie: " + api + "\r\n\r\n");

  Serial.println("request sent");
                  
  while (https.connected()) {
    String line = https.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
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
    
  Serial.println("closing connection");
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
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return -1;
  }
  return doc["count"];
}
