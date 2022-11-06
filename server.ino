#include <WebServer.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


WiFiClient client;

int server_port = 80;//http

void wifiClient_Setup(){
 const char* ssid = "Kinneret College";
 //const char* password = "";
   
    Serial.println("wifiSetup");
   WiFi.begin(ssid);
      //  WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("trying ...");
        delay(100);
    }
    Serial.println("Connected to network");
        digitalWrite(led,HIGH);

}


int GetData() {
  int ret = -1;
  HTTPClient http;
  int carNum = 3; // <<--- change to your car number
  String URL = "http://e2e-race.gil-cohen-portfolio.com/race/get-dir/" + String(carNum);
  http.begin(client, URL);
  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    String Res = http.getString();
    DynamicJsonDocument doc(2048);
    deserializeJson(doc, Res);
    ret = doc["direction"];
    
    delay(200);
  }

  http.end();
  return ret;
}


void checkDriveGrant(){
  HTTPClient http;
  int carNum = 3; // <<--- change to your car number
  String URL = "http://e2e-race.gil-cohen-portfolio.com/race/car-grant/" + String(carNum);
  http.begin(client, URL);
  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    String Res = http.getString();
    DynamicJsonDocument doc(2048);
    deserializeJson(doc, Res);
    isDriveGranted = doc["grant"]; 
    
  }
  http.end();
}
