#include <Arduino.h>
#include <Updater.h>

Updater updater = new Updater();
void setup() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  WiFi.begin("username", "password");

  delay(1000);

  Serial.println("-------------------------");
  Serial.println("Setup");
  Serial.println("-------------------------");

}

void loop() {
  Serial.println("Verzia 5");

delay(5000);
updater.TryUpdate("123", "updater.ino")
}
