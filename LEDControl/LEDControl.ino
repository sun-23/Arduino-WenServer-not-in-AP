#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WifiClient.h>
#include <ESP8266mDNS.h>

ESP8266WebServer server(80);
String webpage = "";
const int pin = D7;
MDNSResponder mdns;

const char* ssid = "iPadSam";
const char* password = "23march2548";

void setup(void) {
  Serial.begin(115200);
  pinMode(pin,OUTPUT);
  digitalWrite(pin, HIGH);
  WiFi.begin(ssid,password);

  while(WiFi.status() !=  WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connect to: ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  if(mdns.begin("esp8266",WiFi.localIP())) {
    Serial.println("MDNS Responder started.");
  }

  
    server.on("/ledon", []{
    digitalWrite(pin,HIGH);
    webpage = "LED is now on.";
    server.send(200, "text/html", webpage);
    delay(1);
   // server.send(200, "text/html" , "CUD58 60043");
    });

    server.on("/ledoff", []{
    digitalWrite(pin,LOW);
    webpage = "LED is now off.";
    server.send(200, "text/html", webpage);
    delay(1);
   // server.send(200, "text/html" , "CUD58 60043");
    });
    server.on("/", []{
    server.send(200, "text/html", "Hello this is the webpage");
    delay(1);
   // server.send(200, "text/html" , "CUD58 60043");
    }); 

       server.begin();
  Serial.print("HTTPS Server started");
}

void loop(void) {
  server.handleClient();
}
