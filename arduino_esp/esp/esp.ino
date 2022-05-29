#include <ESP8266WiFi.h>
#include "index.h"

const char* ssid = "esp_ap";
const char* password = "12345678";

WiFiServer server(80);


volatile uint8_t packet[4] = {0x3a, 0x0, 0x21, 0x0};
volatile uint8_t cmd = 0;

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
  packet[1] = cmd;
  for (int i = 0; i < 3; i++) {
    packet[3] += packet[i];
  }

  //  Serial.write(packet, 4);
  Serial.println((int)cmd);
  delay(100);

  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  client.setNoDelay(true);

  String req = client.readStringUntil('\r');
  client.flush();
  
  if (req.indexOf("/REL/1") != -1) {
    cmd ^= (1 << 0);
    return;
  } else if (req.indexOf("/REL/2") != -1) {
    cmd ^= (1 << 1);
    return;
  } else if (req.indexOf("/ HTTP") != -1) {
    client.print(html);
    client.flush();
    return;
  } else {
    client.stop();
  }
}
