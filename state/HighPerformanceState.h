#ifndef HIGHPERFORMANCESTATE_H
#define HIGHPERFORMANCESTATE_H

#include "State.h"

class HighPerformanceState : public State {
public:
    void apply(MSHSystem* system) override;
    std::string getName() const override;
};

#endif
