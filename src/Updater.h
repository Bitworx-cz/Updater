#include <Arduino.h>

class Updater
{
public:
    Updater(/* args */);
    ~Updater();

    // Optional functionality
    void TryUpdate(char* token);                                       
}