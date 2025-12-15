#ifndef NORMALSTATE_H
#define NORMALSTATE_H

#include "State.h"

class NormalState : public State {
public:
    void apply(MSHSystem* system) override;
    std::string getName() const override;
};

#endif
