#include "securitysystem.h"
#include "modules/devices/Camera.h"
#include "modules/devices/SmokeGasDetector.h"
#include <iostream>

// Constructor implementation
SecuritySystem::SecuritySystem()
    : isSecurityActive(false), logger() {
    std::cout << "Security System Initialized" << std::endl;
}

// Add camera to internal list
void SecuritySystem::addCamera(std::shared_ptr<Camera> camera) {
    cameras.push_back(camera);
}

// Add detector to internal list
void SecuritySystem::addDetector(std::shared_ptr<SmokeGasDetector> detector) {
    detectors.push_back(detector);
}

// Check for motion detection
void SecuritySystem::checkForMotion() {
    if (!isSecurityActive) return; // Return if security inactive

    // Simple motion check: if any camera is turned on, treat as detection
    for (auto& camera : cameras) {
        if (camera->isOn_status()) {
            std::cout << "\n🚨 MOTION DETECTED by Camera " << camera->getId() << std::endl;

            alarmSystem.activateMotionAlarm();
            callPolice();
            logger.info("Motion detected by Camera " + std::to_string(camera->getId()));
            break;
        }
    }
}

// Check for smoke detection
void SecuritySystem::checkForSmoke() {
    // Check all detectors (always active)
    for (auto& detector : detectors) {
        if (detector->isOn_status()) {
            std::cout << "\n🔥 SMOKE DETECTED by Detector " << detector->getId() << std::endl;

            alarmSystem.activateSmokeAlarm();
            logger.info("Smoke detected by Detector " + std::to_string(detector->getId()));
            break;
        }
    }
}

// Simulate motion detection
void SecuritySystem::simulateMotionDetection(int cameraId) {
    std::cout << "\n🔍 Simulating motion detection..." << std::endl;
    for (auto& camera : cameras) {
        if (camera->getId() == cameraId) {
            alarmSystem.activateMotionAlarm();
            logger.info("Simulated motion detection for camera " + std::to_string(cameraId));
            return;
        }
    }
    std::cout << "Camera " << cameraId << " not found!" << std::endl;
}

// Simulate smoke detection
void SecuritySystem::simulateSmokeDetection(int detectorId) {
    std::cout << "\n💨 Simulating smoke detection..." << std::endl;
    for (auto& detector : detectors) {
        if (detector->getId() == detectorId) {
            alarmSystem.activateSmokeAlarm();
            logger.info("Simulated smoke detection for detector " + std::to_string(detectorId));
            return;
        }
    }
    std::cout << "Detector " << detectorId << " not found!" << std::endl;
}

// Call police simulation
void SecuritySystem::callPolice() {
    std::cout << "📞 A call is placed to Police" << std::endl;
    logger.info("Police called");
}