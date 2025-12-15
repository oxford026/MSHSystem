#include "DetectionSystem.h"
#include <iostream>
#include <string>

void DetectionSystem::onSmokeOrGasDetected(Logger& logger) {
    std::cout << "[DETECTION] Smoke/Gas detected! Alarm ON." << std::endl;
    logger.log("Smoke/Gas detected");
    std::cout << "Press ENTER to acknowledge..." << std::endl;
    std::string s;
    std::getline(std::cin, s);
    std::cout << "[DETECTION] Alarm OFF." << std::endl;
}
