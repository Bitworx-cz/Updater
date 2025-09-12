#ifndef UPDATER_H
#define UPDATER_H

#include <Arduino.h>

class Updater
{
public:
    Updater();
    ~Updater();

    void TryUpdate(const char* token, const char* filename);                                       
};

#endif
