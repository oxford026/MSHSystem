#pragma once

#include "State.h"

class HighPerformanceState : public State {
public:
    void apply(MSHSystem* system) override;
    std::string getName() const override;
};
