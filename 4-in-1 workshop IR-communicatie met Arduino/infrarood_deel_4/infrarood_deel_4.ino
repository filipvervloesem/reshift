#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const int ledPin = 4;
const int powerOn[] = { 0xFF40BF, 0xFF08F7, 0xFF08F7, 0xFF08F7, 0xFF08F7, 0xFF08F7, 0xFF48B7 };
const int powerOff[] = { 0xFF40BF };
const int powerOnCmds = 7;
const int powerOffCmds = 1;
const int timeOn = 80000;
const int timeOff = 220000;
String formattedTime;
int timeNow;
int status = 0;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600);
IRsend irsend(ledPin);

void setup()
{
  WiFi.begin("SSID", "PASSWORD");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  timeClient.begin();
  irsend.begin();
}

void loop()
{
  timeClient.update();
  formattedTime = timeClient.getFormattedTime();
  formattedTime.replace(":","");
  timeNow = formattedTime.toInt();
  
  if (status == 0 && timeNow > timeOn && timeNow < timeOff)
  {
    for (int i=0; i<powerOnCmds; i++)
    {
      irsend.sendNEC(powerOn[i], 32, 1);
      delay(250);
    }
    status = 1;
  } else if(status == 1 && timeNow >= timeOff) {
    for (int i=0; i<powerOffCmds; i++)
    {
      irsend.sendNEC(powerOff[i], 32, 1);
      delay(250);
    }
    status = 0;
  }
  delay(60000);
}
