#pragma once
#include "Mode.h"

// Evening mode
class EveningMode : public Mode {
public:
    std::string name() const override { return "Evening"; }

    // Required behavior:
    // Lights OFF, Cameras ON, Smoke & Gas Detectors ON,
    // TV OFF, Music OFF
    void apply(MSHSystem& system) override {
        system.setAllLights(false);
        system.setAllCameras(true);
        system.setAllSmokeGasDetectors(true);
        system.setAllTVs(false);
        system.setAllMusicSystems(false);
    }
};
