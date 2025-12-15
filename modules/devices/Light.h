#ifndef LIGHT_H
#define LIGHT_H

#include "Device.h"

class Light : public Device {
private:
    int brightness;

public:
    Light(int id, const std::string& name, int brightness = 50)
        : Device(id, name), brightness(brightness) {}

    std::string getInfo() const override {
        return "Light [" + name + "]";
    }
};

#endif
