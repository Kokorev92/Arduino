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

  while (WiFi.status() != WL_CONNECTED) {
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
  if (!client) {
    return;
  }

  Serial.println("New client connected");
  while (!client.available()) {
    delay(1);
  }

  String html = "<html>\r\n<body>\r\n<input type=\"button\" id=\"btn_on\" value=\"ON\" style=\"font-size: 64pt;\"/><br/><br/>\r\n<input type=\"button\" id=\"btn_off\" value=\"OFF\" style=\"font-size: 64pt;\"/><br/>\r\n</body>\r\n<script>\r\nbtn_on.onclick = function(){\r\nvar req = new XMLHttpRequest();\r\nreq.open(\"GET\", \"/gpio/1\", true);\r\nreq.send(null);\r\n}\r\nbtn_off.onclick = function(){\r\nvar req = new XMLHttpRequest();\r\nreq.open(\"GET\", \"/gpio/0\", true);\r\nreq.send(null);\r\n}\r\n</script>\r\n</html>";

  String req = client.readStringUntil('\r');
  Serial.println(req);

  client.flush();

  int val;

  if (req.indexOf("/gpio/0") != -1) {
    val = LOW;
  } else if (req.indexOf("gpio/1") != -1) {
    val = HIGH;
  } else if (req.indexOf("/ HTTP") != -1) {
    client.print(html);
    client.flush();
    return;
  } else {
    Serial.println("Invalid request");
    client.stop();
    return;
  }

  digitalWrite(2, val);
  client.flush();
}
