#pragma once

#include "Device.h"

// Music System
// LLR14 - Advanced audio system with equalization and playlist support
class MusicSystem : public Device {
private:
    int volume;
    std::string currentTrack;
    bool isPlaying;
    std::string equalizerMode;

public:
    MusicSystem(int id, const std::string& name, int volume = 15)
        : Device(id, name), volume(volume), currentTrack("None"),
          isPlaying(false), equalizerMode("Normal") {}

    void turnOn() override {
        Device::turnOn();
    }

    void turnOff() override {
        Device::turnOff();
        isPlaying = false;
    }

    // LLR14: Set volume
    void setVolume(int vol) {
        if (vol >= 0 && vol <= 100) {
            volume = vol;
        }
    }

    int getVolume() const {
        return volume;
    }

    // LLR14: Play music
    void play(const std::string& track = "") {
        if (!track.empty()) {
            currentTrack = track;
        }
        if (isOn_status()) {
            isPlaying = true;
        }
    }

    void pause() {
        isPlaying = false;
    }

    void stop() {
        isPlaying = false;
        currentTrack = "None";
    }

    bool getIsPlaying() const {
        return isPlaying;
    }

    std::string getCurrentTrack() const {
        return currentTrack;
    }

    // LLR14: Set equalizer mode
    void setEqualizerMode(const std::string& mode) {
        equalizerMode = mode;
    }

    std::string getEqualizerMode() const {
        return equalizerMode;
    }

    std::string getInfo() const override {
        return "Music System [" + name +
            "] - Volume: " + std::to_string(volume) +
            ", Playing: " + (isPlaying ? "YES" : "NO") +
            ", Track: " + currentTrack +
            ", EQ: " + equalizerMode;
    }
};
