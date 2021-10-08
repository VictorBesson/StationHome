#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

AsyncWebServer server(80);
Preferences preferences;

//put your ssid and password the first time you upload the program
const char* ssid = "";
const char* password = "";

void setup() {
  //Setup And Connecting Serial
  Serial.begin(115200);
  while(!Serial){
  }
  Serial.println();
  Serial.println("Connected to Serial !");

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  //Setup Wifi Preference
  preferences.begin("Credentials", false);
  if(strlen(ssid) == 0){
    ssid = preferences.getString("ssid", "").c_str();
    password = preferences.getString("password", "").c_str();
  }else{
    preferences.putString("ssid", ssid);
    preferences.putString("password", password);
  }
  preferences.end();

  //Connecting to Wifi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
  Serial.print("WiFi connected ! IP : ");
  Serial.println(WiFi.localIP());


  //Setup Route
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "index.html");
  });



}

void loop() {
}