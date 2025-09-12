#include <Arduino.h>
#include "Updater.h"
#include "esp_system.h"
#include "esp_idf_version.h"

#if defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <HTTPClient.h>
#else
#error Architecture unrecognized by this code.
#endif

#include <Update.h>

// Constructor
Updater::Updater() {
    Serial.println("Updater created");
}

// Destructor
Updater::~Updater() {
    Serial.println("Updater destroyed");
}

// Correct member function definition
void Updater::TryUpdate(const char* token, const char* sketchName) {
    HTTPClient http;
    char url[200];
    sprintf(url, "http://espupdater.runasp.net/%s/%s/%012llx/%s",
            token, sketchName, ESP.getEfuseMac(), ESP.getChipModel());
    Serial.println(url);

    http.begin(url);

    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
        int contentLength = http.getSize();
        if (contentLength > 0) {
            bool canBegin = Update.begin(contentLength);
            if (canBegin) {
                Serial.println("Begin OTA update...");
                WiFiClient* client = http.getStreamPtr();
                size_t written = Update.writeStream(*client);

                if (written == contentLength) {
                    Serial.println("Written: " + String(written) + " bytes successfully");
                } else {
                    Serial.println("Written only: " + String(written) + "/" + String(contentLength) + ". Retry?");
                }

                if (Update.end()) {
                    if (Update.isFinished()) {
                        Serial.println("Update finished. Rebooting...");
                        ESP.restart();
                    } else {
                        Serial.println("Update not finished? Something went wrong.");
                    }
                } else {
                    Serial.println("Error occurred. Error #: " + String(Update.getError()));
                }
            } else {
                Serial.println("Not enough space to begin OTA");
            }
        } else {
            Serial.println("Content length is not valid");
        }
    } else {
        Serial.println("Failed to download firmware. HTTP error code: " + String(httpCode));
    }

    http.end();
}
