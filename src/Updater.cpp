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

Updater::Updater(/* args */)
{
}

Updater::~Updater()
{
}

void TryUpdate(char * token, char* sketchName)
{

    HTTPClient http;
    char url[200];
    sprintf(url, "http://espupdater.runasp.net/%s/%s/%012llx/%s", token, sketchName, ESP.getEfuseMac(), ESP.getChipModel());
    Serial.println(url);
    http.begin(url); // Initialize HTTP client with the GitHub URL

    int httpCode = http.GET(); // Send HTTP GET request to download the file

    if (httpCode == HTTP_CODE_OK)
    {
        // If the response is successful, proceed with OTA update
        int contentLength = http.getSize();

        if (contentLength > 0)
        {
            bool canBegin = Update.begin(contentLength);

            if (canBegin)
            {
                Serial.println("Begin OTA update...");

                // Fetch the stream from the HTTP response
                WiFiClient *client = http.getStreamPtr();

                // Update firmware in chunks
                size_t written = Update.writeStream(*client);

                if (written == contentLength)
                {
                    Serial.println("Written : " + String(written) + " successfully");
                }
                else
                {
                    Serial.println("Written only : " + String(written) + "/" + String(contentLength) + ". Retry?");
                }

                // End the update process and check the result
                if (Update.end())
                {
                    if (Update.isFinished())
                    {
                        Serial.println("Update confirmed. Rebooting");
                        ESP.restart();
                    }
                    else
                    {
                        Serial.println("Update not finished? Something went wrong.");
                    }
                }
                else
                {
                    Serial.println("Error Occurred. Error #: " + String(Update.getError()));
                }
            }
            else
            {
                Serial.println("Not enough space to begin OTA");
            }
        }
        else
        {
            Serial.println("Content length is not valid");
        }
    }
    else
    {
        Serial.println("Failed to download firmware. HTTP error code: " + String(httpCode));
    }

    http.end(); // Close the HTTP connection
}