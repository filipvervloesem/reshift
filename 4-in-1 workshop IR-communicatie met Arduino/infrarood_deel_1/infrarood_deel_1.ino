#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600);

void setup()
{
  Serial.begin(9600);

  WiFi.begin("SSID", "PASSWORD");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Ip-adres: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();
}

void loop()
{
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
  delay(1000);
}
