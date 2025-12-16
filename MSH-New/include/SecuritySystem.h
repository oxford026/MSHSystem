#ifndef SECURITYSYSTEM_H
#define SECURITYSYSTEM_H

#include "Logger.h"

class SecuritySystem {
public:
    void onMotionDetected(Logger& logger);
};

#endif
