#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "MyHomeWIFI";
const char* passwd = "gtl53wqm41";
const uint8_t ID = 0x56;

WiFiUDP udp;
const int port = 5500;
char in_buff[255];

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }

  Serial.print("Conneted to: ");
  Serial.println(ssid);

  udp.begin(port);
}

void loop() {
  int pack_size = udp.parsePacket();
  if (pack_size) {
    int len = udp.read(in_buff, 255);
    if (len > 0) {
      if ((in_buff[0] == 'R') && (in_buff[1] == 'Q')) {
        if (in_buff[2] == ID) {
          udp.beginPacket(udp.remoteIP(), udp.remotePort());
          udp.write("I am here: ");
          udp.write(WiFi.localIP().toString().c_str());
          udp.write("\n");
          udp.endPacket();
          Serial.print("Request from: ");
          Serial.print(udp.remoteIP());
          Serial.print(" ");
          Serial.println(udp.remotePort());
        } else {
          Serial.println("Correct request, but not for me!");
        }
      }
    }

  }
}
