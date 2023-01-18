#include <Arduino.h>
#include <ESP8266WebServer.h>

#include "secrets.h"  // add WLAN Credentials in here.
// #include "builtinfiles.h" TODO

// mark parameters not used in example
//#define UNUSED __attribute__((unused))

#define HOSTNAME "webserver"
#define TIMEZONE "CET-1CEST,M3.5.0,M10.5.0/3"

ESP8266WebServer server(80);


void handleSysInfo() {
  String result;

  result += "{\n";
  result += "  \"flashSize\": " + ",\n";
  result += "  \"freeHeap\": " + ";
  result += "  \"fsTotalBytes\": " + "\n";
  result += "  \"fsUsedBytes\": " + "\n";
  result += "}";

  server.sendHeader("Cache-Control", "no-cache");
  server.send(200, "text/javascript; charset=utf-8", result);
}

void setup(void) {
  delay(3000);
  Serial.begin(9600);
  Serial.setDebugOutput(false);

  WiFi.mode(WIFI_STA);
  if (strlen(ssid) == 0) {
    WiFi.begin();
  } else {
    WiFi.begin(ssid, passPhrase);
  }

  WiFi.setHostname(HOSTNAME);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  configTime(TIMEZONE, "pool.ntp.org");

  server.on("/", HTTP_GET, handleRedirect);

  server.enableCORS(true);

  server.onNotFound([]() {
    server.send(404, "text/html", "<h1>content not found.</h1>");
  });

  server.begin();
}


// run the server...
void loop(void) {
  server.handleClient();
}  // loop()

// end.
