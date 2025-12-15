#ifndef MUSICSYSTEM_H
#define MUSICSYSTEM_H

#include "Device.h"

// Music System
// LLR14
class MusicSystem : public Device {
private:
    int volume;

public:
    MusicSystem(int id, const std::string& name, int volume = 15)
        : Device(id, name), volume(volume) {}

    std::string getInfo() const override {
        return "Music System [" + name +
            "] - Volume: " + std::to_string(volume);
    }
};

#endif
