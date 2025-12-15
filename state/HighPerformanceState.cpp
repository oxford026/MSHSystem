#include "HighPerformanceState.h"
#include "MSHSystem.h"

void HighPerformanceState::apply(MSHSystem* system) {
    system->setCameraPerformance("HIGH");
    system->setLightMode("MAX");
    system->setPowerSaving(false);
}

std::string HighPerformanceState::getName() const {
    return "High Performance";
}
