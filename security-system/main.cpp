#include "SecuritySystem.h"
#include "DetectionSystem.h"
#include "Logger.h"
#include <iostream>

int main() {
    Logger logger;
    SecuritySystem security;
    DetectionSystem detection;

    std::cout << "1) Simulate Motion\n";
    std::cout << "2) Simulate Smoke/Gas\n";
    std::cout << "Choose: ";

    int choice = 0;
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 1) {
        security.onMotionDetected(logger);
    } else if (choice == 2) {
        detection.onSmokeOrGasDetected(logger);
    } else {
        std::cout << "Invalid choice." << std::endl;
    }

    return 0;
}
