#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const int ledPin = 4;
const int power = 0xFF40BF;
  
IRsend irsend(ledPin);

void setup() {
  irsend.begin();
}

void loop() {
  irsend.sendNEC(power, 32, 1);
  delay(10000);
}
