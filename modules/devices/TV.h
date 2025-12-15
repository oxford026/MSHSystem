#ifndef TV_H
#define TV_H

#include "Device.h"

// TV device
// LLR14
class TV : public Device {
private:
    std::string brand;
    int volume;

public:
    TV(int id, const std::string& name,
        const std::string& brand = "Generic",
        int volume = 10)
        : Device(id, name), brand(brand), volume(volume) {}

    std::string getInfo() const override {
        return "TV [" + name +
            "] - Brand: " + brand +
            ", Volume: " + std::to_string(volume);
    }
};

#endif
