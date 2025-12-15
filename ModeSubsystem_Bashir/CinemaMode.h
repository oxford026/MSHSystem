#pragma once
#include "Mode.h"

// Cinema mode
class CinemaMode : public Mode {
public:
    std::string name() const override { return "Cinema"; }

    // NOTE: The document clearly defines Party & Evening behavior.
    // Cinema is typically: Lights OFF, TV ON, Cameras ON, Detector ON, Music OFF.
    // If your group has a different Cinema definition, we will adjust later.
    void apply(MSHSystem& system) override {
        system.setAllLights(false);
        system.setAllCameras(true);
        system.setAllSmokeGasDetectors(true);
        system.setAllTVs(true);
        system.setAllMusicSystems(false);
    }
};
