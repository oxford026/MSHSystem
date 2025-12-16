#pragma once

#include "Device.h"

// Camera device
// LLR14 - Advanced camera with recording and night vision
class Camera : public Device {
private:
    int fps;
    bool nightVision;
    bool recording;
    std::string resolution;

public:
    Camera(int id, const std::string& name, int fps = 30, bool nightVision = false)
        : Device(id, name), fps(fps), nightVision(nightVision), 
          recording(false), resolution("1080p") {}

    void turnOn() override {
        Device::turnOn();
        recording = false;
    }

    void turnOff() override {
        Device::turnOff();
        recording = false;
    }

    // LLR14: Start recording
    void startRecording() {
        if (isOn_status()) {
            recording = true;
        }
    }

    // LLR14: Stop recording
    void stopRecording() {
        recording = false;
    }

    bool isRecording() const {
        return recording;
    }

    // LLR14: Set resolution
    void setResolution(const std::string& res) {
        resolution = res;
    }

    std::string getResolution() const {
        return resolution;
    }

    // LLR14: Toggle night vision
    void toggleNightVision() {
        nightVision = !nightVision;
    }

    std::string getInfo() const override {
        return "Camera [" + name + "] - FPS: " + std::to_string(fps) +
            ", Night Vision: " + (nightVision ? "ON" : "OFF") +
            ", Resolution: " + resolution +
            ", Recording: " + (recording ? "YES" : "NO");
    }
};
