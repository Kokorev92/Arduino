#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

String html = "<html>\n"
              "  <head><title>ESP SERVER</title></head>\n"
              "  <body>Hello world!</body>\n"
              "</html>";

const char *ssid = "esp_server";
const char *password = "12345678";
const char *server_name = "www.esp.com";
const byte DNS_PORT = 53;

DNSServer dnsServer;

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  //  WiFi.mode(WIFI_AP);
  IPAddress apIP = IPAddress(10, 0, 0, 1);
  delay(5000);
  Serial.println(WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)) ? "OK" : "ERR");

  WiFi.softAP(ssid, password);
  delay(100);

  dnsServer.start(DNS_PORT, server_name, apIP);
  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
}
