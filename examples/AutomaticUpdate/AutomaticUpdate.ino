#include <Arduino.h>
#include <Updater.h>
#include <WiFi.h>

Updater updater;

void setup() {
  Serial.begin(115200);
  WiFi.begin("username", "password");

  delay(1000);

  Serial.println("-------------------------");
  Serial.println("Setup");
  Serial.println("-------------------------");
}

void loop() {
  Serial.println("Verzia 5");
  delay(5000);

  updater.TryUpdate("token", "AutomaticUpdate.ino");
}
