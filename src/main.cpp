#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

//define for temperature
#define LM_35_SENSOR1 A0
#define ADC_RESOLUTION 4096.0
#define ADC_VREF_mV 5000

AsyncWebServer server(80);
Preferences preferences;

//put your ssid and password the first time you upload the program
String ssid = "";
String password = "";


float temperature = 0;

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
  if(ssid.length() == 0){
    ssid = preferences.getString("ssid", "none");
    password = preferences.getString("pass", "none");
  }else{
    preferences.putString("ssid", ssid);
    preferences.putString("pass", password);
  }
  preferences.end();
  

  //Connecting to Wifi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
  Serial.print("WiFi connected ! IP : ");
  Serial.println(WiFi.localIP());


  //Setup Route
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/index.html");
  });

  server.begin();

}

void loop() {
  //read the temperature
  int adcVal = analogRead(LM_35_SENSOR1);
  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
  temperature = milliVolt / 10;
  Serial.println(temperature);
  delay(1000);
}