#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

#include <SoftwareSerial.h>

SoftwareSerial esp(7, 8); //rx, tx
IRsend ir_send;

const int BUFFER_SIZE = 512;
char buffer[BUFFER_SIZE];

void setup() {
  memset(buffer, char(0x00), BUFFER_SIZE);
  Serial.begin(115200);
  esp.begin(115200);
  esp.println("AT+RST");
  delay(1000);
  esp.println("AT+CWMODE=1");
  delay(1000);
  esp.println("AT+CWJAP=\"MyHomeWIFI\",\"gtl53wqm41\"");
  delay(5000);
  esp.println("AT+CIPMODE=0");
  delay(1000);
  esp.println("AT+CIPMUX=1");
  delay(1000);
  esp.println("AT+CIPSERVER=1,1555");
  delay(1000);
}

void loop()  {
  static int i = 0;
  while (esp.available()) {
    buffer[i++] = esp.read();
  }

  if (i > 1) {
    Serial.println(buffer);
    run_command();
    i = 0;
    memset(buffer, char(0x00), BUFFER_SIZE);
  }
}

void run_command() {
  int ch_id = 0, packet_len = 0, command = 0;
  char *pb;

  sscanf(buffer, "+IPD,%d,%d", &ch_id, &packet_len);
  Serial.print("Channel: ");
  Serial.println(ch_id);
  Serial.print("Packet length: ");
  Serial.println(packet_len);
  pb = buffer + 5;
  while (*pb != ':') pb++;
  pb++;
  Serial.print("Command: ");
  Serial.println(*pb);
  switch (*pb) {
    case '0' :
      ir_send.sendNEC(0x830CF, 32);
      break;
    case '1' :
      ir_send.sendNEC(0x8C03F, 32);
      break;
    case '2' :
      ir_send.sendNEC(0x820DF, 32);
      break;
    case '3' :
      ir_send.sendNEC(0x8A05F, 32);
      break;
    case '4' :
      ir_send.sendNEC(0x8609F, 32);
      break;
    case '5' :
      ir_send.sendNEC(0x8E01F, 32);
      break;
    case '6' :
      ir_send.sendNEC(0x810EF, 32);
      break;
    case '7' :
      ir_send.sendNEC(0x8906F, 32);
      break;
    case '8' :
      ir_send.sendNEC(0x850AF, 32);
      break;
    case '9' :
      ir_send.sendNEC(0x8D02F, 32);
      break;
  };
}
