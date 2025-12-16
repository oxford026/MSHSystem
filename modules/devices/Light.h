#pragma once

#include "Device.h"

class Light : public Device {
private:
    int brightness;
    std::string colorTemperature;  // Warm, Neutral, Cool
    bool dimmerSupport;

public:
    Light(int id, const std::string& name, int brightness = 50)
        : Device(id, name), brightness(brightness), 
          colorTemperature("Neutral"), dimmerSupport(true) {}

    // Set brightness level
    void setBrightness(int level) {
        if (level >= 0 && level <= 100) {
            brightness = level;
        }
    }

    int getBrightness() const {
        return brightness;
    }

    // Set color temperature
    void setColorTemperature(const std::string& temp) {
        colorTemperature = temp;
    }

    std::string getColorTemperature() const {
        return colorTemperature;
    }

    bool isDimmerSupported() const {
        return dimmerSupport;
    }

    std::string getInfo() const override {
        return "Light [" + name + "] - Brightness: " + std::to_string(brightness) +
            "%, Color Temp: " + colorTemperature + 
            ", Dimmable: " + (dimmerSupport ? "YES" : "NO");
    }
};
