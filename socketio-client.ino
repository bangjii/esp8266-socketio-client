#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <SocketIoClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;
SocketIoClient webSocket;
String inputString;
void event(const char * payload, size_t length) {
  USE_SERIAL.printf("got message: %s\n", payload);
}

void setup() {
    USE_SERIAL.begin(115200);
    USE_SERIAL.setDebugOutput(true);
    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();
    for(uint8_t t = 4; t > 0; t--) {
      USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
      USE_SERIAL.flush();
      delay(1000);
    }
    WiFiMulti.addAP("ws-it", "aMz*123#");
    while(WiFiMulti.run() != WL_CONNECTED) {
      delay(100);
    }

    webSocket.on("message", event);
    webSocket.begin("socketio-server.bangjii.repl.co");
}

void loop() {
    webSocket.loop();
    while (Serial.available()) {
      char inChar = (char)Serial.read();
      inputString += inChar;
      if (inChar == '\n') {
        inputString.trim();
        String asd = "\"" + inputString + "\"";
        webSocket.emit("message", asd.c_str());
        inputString = "";
      }
    }
}
