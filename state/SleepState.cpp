#include "SleepState.h"
#include "MSHSystem.h"

void SleepState::apply(MSHSystem* system) {
    system->turnOffNonEssentialDevices();
    system->setCameraPerformance("LOW");
    system->setPowerSaving(true);
}

std::string SleepState::getName() const {
    return "Sleep";
}
