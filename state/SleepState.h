#ifndef SLEEPSTATE_H
#define SLEEPSTATE_H

#include "State.h"

class SleepState : public State {
public:
    void apply(MSHSystem* system) override;
    std::string getName() const override;
};

#endif
