#pragma once

#include <iostream>
#include "Device.h"

// Smoke & Gas Detector
// LLR14, LLR46 - Advanced safety detector with alerts and calibration
class SmokeGasDetector : public Device {
private:
    int sensitivity;
    bool alertActive;
    int batteryLevel;
    bool selfTestEnabled;

public:
    SmokeGasDetector(int id, const std::string& name, int sensitivity = 5)
                : Device(id, name), sensitivity(sensitivity), alertActive(false),
                    batteryLevel(100), selfTestEnabled(false) {
                // Detectors are critical devices and should be powered on by default
                turnOn();
        }

    // LLR46: Set sensitivity level
    void setSensitivity(int level) {
        if (level >= 1 && level <= 10) {
            sensitivity = level;
        }
    }

    int getSensitivity() const {
        return sensitivity;
    }

    // LLR46: Trigger alert
    void triggerAlert() {
        if (isOn_status()) {
            alertActive = true;
        }
    }

    void clearAlert() {
        alertActive = false;
    }

    bool isAlertActive() const {
        return alertActive;
    }

    // LLR46: Battery monitoring
    void setBatteryLevel(int level) {
        if (level >= 0 && level <= 100) {
            batteryLevel = level;
        }
    }

    int getBatteryLevel() const {
        return batteryLevel;
    }

    bool isBatteryLow() const {
        return batteryLevel < 20;
    }

    // LLR46: Self-test capability
    void performSelfTest() {
        selfTestEnabled = true;
    }

    void completeSelfTest() {
        selfTestEnabled = false;
    }

    void turnOff() override {
        // Prevent powering off detectors; they must remain active
        std::cout << "Detector cannot be powered off; operation unchanged." << std::endl;
    }

    bool isSelftestRunning() const {
        return selfTestEnabled;
    }

    std::string getInfo() const override {
        return "Smoke & Gas Detector [" + name +
            "] - Sensitivity: " + std::to_string(sensitivity) +
            ", Alert: " + (alertActive ? "ACTIVE" : "INACTIVE") +
            ", Battery: " + std::to_string(batteryLevel) + "%" +
            ", SelfTest: " + (selfTestEnabled ? "RUNNING" : "IDLE");
    }
};
