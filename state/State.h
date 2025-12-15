#ifndef STATE_H
#define STATE_H

#include <string>

class MSHSystem;

class State {
public:
    virtual ~State() = default;
    virtual void apply(MSHSystem* system) = 0;
    virtual std::string getName() const = 0;
};

#endif
