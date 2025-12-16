#pragma once

#include <string>
#include "DeviceStatus.h"

class Device {
protected:
    int id;
    std::string name;
    bool isOn;
    DeviceStatus status;

public:
    Device(int id, const std::string& name)
        : id(id), name(name), isOn(false), status(DeviceStatus::ACTIVE) {}

    virtual ~Device() = default;

    int getId() const { return id; }
    const std::string& getName() const { return name; }
    bool isOn_status() const { return isOn; }
    DeviceStatus getStatus() const { return status; }

    virtual void turnOn() {
        if (status != DeviceStatus::FAILED) {
            isOn = true;
            status = DeviceStatus::ACTIVE;
        }
    }

    virtual void turnOff() {
        isOn = false;
    }

    virtual void fail() {
        status = DeviceStatus::FAILED;
        isOn = false;
    }

    virtual std::string getInfo() const = 0;
};
