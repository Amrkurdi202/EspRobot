#include <WiFi.h>
#include <WiFiUdp.h>
#include "WiFiHandler.h"
#include "MotorHandler.h"
#include "ServoHandler.h"

#define SSID "ras" // WiFi SSID
#define PASSWORD "12345678" // WiFi Password
#define LOCAL_PORT 8888 // UDP Port

extern WiFiUDP udp;
extern ESP32ServoLite servo;
extern MX1508 motor1;
extern MX1508 motor2;

unsigned long lastPacketTime = 0;
byte lastDirection = 0;
const unsigned long timeout = 250;

WiFiUDP udp;

void WiFiEvent(WiFiEvent_t event) {
  if (event == ARDUINO_EVENT_WIFI_STA_GOT_IP) brodcastIp();
}

void brodcastIp() {
  String message = WiFi.localIP().toString() + " dragon";
  udp.beginPacket("255.255.255.255", 5555);
  udp.write((const uint8_t*)message.c_str(), message.length());
  udp.endPacket();
  Serial.println("Broadcasted: " + message);
}

void setupWiFi() {
  WiFi.onEvent(WiFiEvent);
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.println(WiFi.localIP());
}

void setupUDP() {
  udp.begin(LOCAL_PORT);
  Serial.println("UDP listening started");
}

void loopUDP() {
  int packetSize = udp.parsePacket();
  if (packetSize >= 4) {
    byte buffer[4];
    udp.read(buffer, 4);

    byte version = buffer[0];
    byte cmd = buffer[1];
    byte name = buffer[2];
    byte value = buffer[3];

    if (version != 1) return;

    if (cmd == 2 && name == 10) {
      if (value != lastDirection) {
        lastDirection = value;
        handleJoystick(value);
      }
      lastPacketTime = millis();
    }

    if (cmd == 2 && name == 9) setLaser(value);
    if (cmd == 2 && name == 11) {
      Serial.print("Servo value: ");
      Serial.println(value);
      servo.write(value);
    }
  }
}
