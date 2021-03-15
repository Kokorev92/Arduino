#include <ESP8266WiFi.h>
#include "index.h"

const char* ssid = "MyHomeWIFI";
const char* password = "gtl53wqm41";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

    server.begin();
  }

  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  while (!client.available()) {
    delay(1);
  }

  String req = client.readStringUntil('\r');

  client.flush();

  if (req.indexOf("/gpio/5") != -1) {
    Serial.write(0x53);
  } else if (req.indexOf("gpio/1") != -1) {
    Serial.write(0x46);
  } else if (req.indexOf("/gpio/3") != -1) {
    Serial.write(0x4C);
  } else if (req.indexOf("/gpio/2") != -1){
    Serial.write(0x42);
  } else if (req.indexOf("/gpio/4") != -1) {
    Serial.write(0x52);
  } else if (req.indexOf("/ HTTP") != -1) {
    client.print(html);
    client.flush();
    return;
  } else {
    client.stop();
    return;
  }

  client.flush();
}
