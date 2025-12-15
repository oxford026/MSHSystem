#pragma once
#include <string>

class MSHSystem;

// Strategy / State interface for system modes
class Mode {
public:
    virtual ~Mode() = default;

    // Returns the mode name (Normal, Evening, Party, Cinema)
    virtual std::string name() const = 0;

    // Applies the mode behavior to the system
    virtual void apply(MSHSystem& system) = 0;
};
