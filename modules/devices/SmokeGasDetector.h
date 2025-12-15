#ifndef SMOKEGASDETECTOR_H
#define SMOKEGASDETECTOR_H

#include "Device.h"

// Smoke & Gas Detector
// LLR14, LLR46
class SmokeGasDetector : public Device {
private:
    int sensitivity;

public:
    SmokeGasDetector(int id, const std::string& name, int sensitivity = 5)
        : Device(id, name), sensitivity(sensitivity) {}

    std::string getInfo() const override {
        return "Smoke & Gas Detector [" + name +
            "] - Sensitivity: " + std::to_string(sensitivity);
    }
};

#endif
