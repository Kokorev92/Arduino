#include <ESP8266WiFi.h>

const char* ssid = "secret_point";
const char* password = "00000000";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");

    Serial.println();
    Serial.println("WiFi connected");

    server.begin();
    Serial.println("Server started!");
    Serial.println(WiFi.localIP());
  }
}

void loop() {
  WiFiClient client = server.available();
  if(!client) {
    return;
  }

  Serial.println("New client connected");
  while(!client.available()){
    delay(1);
  }

  String req = client.readStringUntil('\r');
  Serial.println(req);

  client.flush();

  int val;

  if(req.indexOf("/gpio/0") != -1){
    val = LOW;
  } else if(req.indexOf("gpio/1") != -1){
    val = HIGH;
  } else {
    Serial.println("Invalid request");
    client.stop();
    return;
  }

  digitalWrite(2, val);
  client.flush();

  String ans = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n>html>\r\nGPIO is now ";
  ans += (val) ? "high" : "low";
  ans += "</html>\n";

  client.print(ans);
}
