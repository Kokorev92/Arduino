#include <ESP8266WiFi.h>

const char* ssid = "esp_ap";
const char* password = "12345678";

WiFiServer server(80);

void setup() {
  Serial.begin(19200);

  WiFi.mode(WIFI_AP);
  if (WiFi.softAP(ssid, password)) {
    Serial.println("Soft-AP strted!");
  }

  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  client.setNoDelay(true);

  while (client.connected()) {
    while (client.available()) {
      Serial.write(client.read());
    }
  }
}
