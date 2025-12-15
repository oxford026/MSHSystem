#include "NormalState.h"
#include "MSHSystem.h"

void NormalState::apply(MSHSystem* system) {
    system->setCameraPerformance("NORMAL");
    system->setLightMode("NORMAL");
    system->setPowerSaving(false);
}

std::string NormalState::getName() const {
    return "Normal";
}
