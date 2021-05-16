#include <ESP8266WiFi.h>

const char* ssid = "secret_point";
const char* password = "00000000";

WiFiServer server(80);

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.println("Client connected");

  while (client.connected()) {
    String req = client.readStringUntil('\r');
    Serial.println(req);
    if (req.indexOf("on") != -1) {
      Serial.write(0x01);
    } else if (req.indexOf("off") != -1) {
      Serial.write(0x00);
    }

    while (client.available()) {
      client.read();
    }
  }
}
