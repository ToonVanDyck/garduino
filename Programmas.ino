#include "Adafruit_seesaw.h"

Adafruit_seesaw ss;
int relaisPin = 16; 
int stat = 0;
String programma;
int n = 0;

// app
#include <ESP8266WiFi.h>
const char WiFiPassword[] = "Garduino1"; 
const char AP_NameChar[] = "Garduino" ; //EmbeddedGate
 
WiFiServer server(80);
 
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html><html><head><title>LED Control</title></head><body><div id='main'><h2>LED Control</h2>";
String html_2 = "<form id='F1' action='LEDON'><input class='button' type='submit' value='LED ON' ></form><br>";
String html_3 = "<form id='F2' action='LEDOFF'><input class='button' type='submit' value='LED OFF' ></form><br>";
String html_4 = "</div></body></html>";
 
String request = "";
// app

void Tomaat_prog() {
  int T_water = 10000;
  int tussentijd = 2000;
  int aantal = 1;
  for (n=0;n<aantal;n++) {
    digitalWrite(relaisPin, LOW);
    delay(T_water);
    digitalWrite(relaisPin,HIGH);
    delay(tussentijd);
  }
}

void Komkommer_prog() {
  int T_water = 2000;
  int tussentijd = 1000;
  int aantal = 1;
  for (n=0;n<aantal;n++) {
    digitalWrite(relaisPin, LOW);
    delay(T_water);
    digitalWrite(relaisPin,HIGH);
    delay(tussentijd);
  }
}

void Sla_prog() {
  int T_water = 12000;
  int tussentijd = 5000;
  int aantal = 1;
  for (n=0;n<aantal;n++) {
    digitalWrite(relaisPin, HIGH);
    delay(T_water);
    digitalWrite(relaisPin,LOW);
    delay(tussentijd);
  }
}
void Aardbijen_prog() {
  int T_water = 7000;
  int tussentijd = 1000;
  int aantal = 1;
  for (n=0;n<aantal;n++) {
    digitalWrite(relaisPin, HIGH);
    delay(T_water);
    digitalWrite(relaisPin,LOW);
    delay(tussentijd);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(relaisPin, OUTPUT);
  Serial.begin(115200);
  // app
  pinMode(relaisPin, OUTPUT); 
  boolean conn = WiFi.softAP(AP_NameChar, WiFiPassword);
  server.begin();
  // app
  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }
}

void loop() {
  uint16_t capread = ss.touchRead(0);
  Serial.print("Capacitive: "); Serial.println(capread);
  delay(100);
  Serial.println(stat);
  programma = "komkommer";

  // app
  // Check if a client has connected
   WiFiClient client = server.available();
  //  if (!client)  {  return;  }
 
    // Read the first line of the request
    request = client.readStringUntil('\r');

 
    if  ( request.indexOf("LEDON") > 0 || stat == 1)  
      { digitalWrite(relaisPin, LOW);
      stat = 1; }      
    if ( request.indexOf("LEDOFF") > 0 or stat == 0) { 
      stat = 0;
      }
    if (capread < 600 and stat == 1) {
        Serial.println(stat);
        if (programma == "tomaat") {
          Tomaat_prog();
        }
        else if(programma == "komkommer") {
          Komkommer_prog();
        }
        else if(programma == "sla") {
          Sla_prog();
        }
        else if(programma == "aardbij") {
          Aardbijen_prog();
        }
    else {
          digitalWrite(relaisPin,LOW);
        }
      }
    client.flush();
    client.print( header );
    client.print( html_1 );
    client.print( html_2 );
    client.print( html_3 );
    client.print( html_4);
    // delay  
      }
