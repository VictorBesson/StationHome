#include <Arduino.h>
#include <Preferences.h>

Preferences preferences;

//put your ssid and password the first time you upload the program
String ssid = "";
String password = "";

void setup() {
  //Setup Serial
  Serial.begin(115200);
  while(!Serial){
  }
  Serial.println();
  Serial.println("Connected to Serial !");

  //Setup Wifi Preference
  preferences.begin("Credentials", false);
  if(ssid.length() == 0){
    ssid = preferences.getString("ssid", "");
    password = preferences.getString("password", "");
  }else{
    preferences.putString("ssid", ssid);
    preferences.putString("password", password);
  }
  preferences.end();

  

}

void loop() {
}