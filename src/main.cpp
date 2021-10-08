#include <Arduino.h>



void setup() {
  //Setup Serial
  Serial.begin(115200);
  while(!Serial){
  }
  Serial.println();
  Serial.println("Connected to Serial !");



}

void loop() {
}