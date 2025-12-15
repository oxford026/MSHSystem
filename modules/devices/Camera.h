#ifndef CAMERA_H
#define CAMERA_H

#include "Device.h"

// Camera device
// LLR14
class Camera : public Device {
private:
    int fps;
    bool nightVision;

public:
    Camera(int id, const std::string& name, int fps = 30, bool nightVision = false)
        : Device(id, name), fps(fps), nightVision(nightVision) {}

    std::string getInfo() const override {
        return "Camera [" + name +
            "] - FPS: " + std::to_string(fps) +
            ", Night Vision: " + (nightVision ? "ON" : "OFF");
    }
};

#endif
