#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WifiClient.h>
#include <ESP8266mDNS.h>

ESP8266WebServer server(80);

MDNSResponder mdns;

const char* ssid = "iPadSam";
const char* password = "23march2548";

void setup(void) {
  Serial.begin(115200);
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

  server.on("/", []{
    server.send(200, "text/html" , "Hello, world");
    });
  server.begin();
  Serial.print("HTTPS Server started");
}

void loop(void) {
  server.handleClient();
}
