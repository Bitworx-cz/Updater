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
Updater::Updater()
{
    lastCheck = 0;
}

// Destructor
Updater::~Updater()
{
}

// Correct member function definition
void Updater::TryUpdate(const char *token, const char *sketchName)
{

    if (millis() < lastCheck)
    {
        lastCheck = 0;
    }

    if (millis() - lastCheck < 600000)
    {
        return;
    }

    lastCheck = millis();
    HTTPClient http;
    char url[200];
    sprintf(url, "http://espupdater.runasp.net/%s/%s/%012llx/%s",
            token, sketchName, ESP.getEfuseMac(), ESP.getChipModel());
    Serial.println(url);

    http.begin(url);

    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK)
    {
        int contentLength = http.getSize();
        if (contentLength > 0)
        {
            bool canBegin = Update.begin(contentLength);
            if (canBegin)
            {
                WiFiClient *client = http.getStreamPtr();
                size_t written = Update.writeStream(*client);

                if (written == contentLength)
                {
                    if (Update.end())
                    {
                        if (Update.isFinished())
                        {
                            char udUrl[200];
                            sprintf(udUrl, "http://espupdater.runasp.net/ud/%s/%s/%012llx/%s",
                                    token, sketchName, ESP.getEfuseMac(), ESP.getChipModel());
                            Serial.println(udUrl);
                            http.begin(udUrl);
                            http.GET();
                            http.end();
                            ESP.restart();
                        }
                    }
                }
            }
        }
    };
    http.end();
}
