#ifndef DETECTIONSYSTEM_H
#define DETECTIONSYSTEM_H

#include "Logger.h"

class DetectionSystem {
public:
    void onSmokeOrGasDetected(Logger& logger);
};

#endif
