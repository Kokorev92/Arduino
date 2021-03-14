#include <ESP8266WiFi.h>

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
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  while (!client.available()) {
    delay(1);
  }

  String html = "<html>\r\n<body>\r\n<input type=\"button\" id=\"btn_on\" value=\"FORWARD\" style=\"font-size: 64pt;\"/><br/><br/>\r\n<input type=\"button\" id=\"btn_off\" value=\"STOP\" style=\"font-size: 64pt;\"/><br/>\r\n</body>\r\n<script>\r\nbtn_on.onclick = function(){\r\nvar req = new XMLHttpRequest();\r\nreq.open(\"GET\", \"/gpio/1\", true);\r\nreq.send(null);\r\n}\r\nbtn_off.onclick = function(){\r\nvar req = new XMLHttpRequest();\r\nreq.open(\"GET\", \"/gpio/0\", true);\r\nreq.send(null);\r\n}\r\n</script>\r\n</html>";

  String req = client.readStringUntil('\r');

  client.flush();

  if (req.indexOf("/gpio/0") != -1) {
    Serial.write(0x53);
  } else if (req.indexOf("gpio/1") != -1) {
    Serial.write(0x46);
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
