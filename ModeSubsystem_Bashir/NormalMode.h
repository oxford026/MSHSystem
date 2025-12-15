#pragma once
#include "Mode.h"

// Normal mode (baseline/default)
class NormalMode : public Mode {
public:
    std::string name() const override { return "Normal"; }

    // This will call helper functions in MSHSystem (implemented by the core team)
    void apply(MSHSystem& system) override {
        system.setAllLights(false);
        system.setAllCameras(false);
        system.setAllSmokeGasDetectors(true);
        system.setAllTVs(false);
        system.setAllMusicSystems(false);
    }
};
