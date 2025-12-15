#pragma once
#include "Mode.h"

// Party mode
class PartyMode : public Mode {
public:
    std::string name() const override { return "Party"; }

    // Required behavior:
    // Lights ON, Cameras ON, Smoke & Gas Detectors ON,
    // TV OFF, Music ON
    void apply(MSHSystem& system) override {
        system.setAllLights(true);
        system.setAllCameras(true);
        system.setAllSmokeGasDetectors(true);
        system.setAllTVs(false);
        system.setAllMusicSystems(true);
    }
};
