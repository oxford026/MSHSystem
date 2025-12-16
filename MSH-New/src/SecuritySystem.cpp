#include "SecuritySystem.h"
#include <iostream>

void SecuritySystem::onMotionDetected(Logger& logger) {
    std::cout << "[SECURITY] Motion detected! Alarm ON." << std::endl;
    std::cout << "[SECURITY] A call is placed to Police." << std::endl;
    logger.log("Motion detected");
}
