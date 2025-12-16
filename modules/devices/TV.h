#pragma once

#include "Device.h"

// TV device
// LLR14 - Advanced TV with source switching and picture modes
class TV : public Device {
private:
    std::string brand;
    int volume;
    std::string inputSource;
    std::string pictureMode;
    bool smartFeatures;

public:
    TV(int id, const std::string& name,
        const std::string& brand = "Generic",
        int volume = 10)
        : Device(id, name), brand(brand), volume(volume),
          inputSource("HDMI1"), pictureMode("Standard"), smartFeatures(true) {}

    // LLR14: Adjust volume
    void setVolume(int vol) {
        if (vol >= 0 && vol <= 100) {
            volume = vol;
        }
    }

    int getVolume() const {
        return volume;
    }

    // LLR14: Change input source
    void setInputSource(const std::string& source) {
        inputSource = source;
    }

    std::string getInputSource() const {
        return inputSource;
    }

    // LLR14: Set picture mode
    void setPictureMode(const std::string& mode) {
        pictureMode = mode;
    }

    std::string getPictureMode() const {
        return pictureMode;
    }

    // LLR14: Toggle smart features
    void toggleSmartFeatures() {
        smartFeatures = !smartFeatures;
    }

    bool hasSmartFeatures() const {
        return smartFeatures;
    }

    std::string getInfo() const override {
        return "TV [" + name +
            "] - Brand: " + brand +
            ", Volume: " + std::to_string(volume) +
            ", Source: " + inputSource +
            ", Mode: " + pictureMode +
            ", Smart: " + (smartFeatures ? "ON" : "OFF");
    }
};
