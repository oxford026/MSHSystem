#pragma once

#include <string>
#include <vector>
#include "Logger.h"

enum class DetectionType {
    MOTION,
    SMOKE,
    GAS,
    INTRUSION
};

struct Detection {
    DetectionType type;
    std::string location;
    std::string timestamp;
    bool isActive;

    Detection(DetectionType t, const std::string& loc)
        : type(t), location(loc), isActive(true) {}
};

class DetectionSystem {
private:
    std::vector<Detection> detections;
    Logger* logger;
    bool systemArmed;

public:
    DetectionSystem() : logger(nullptr), systemArmed(false) {}

    void setLogger(Logger* log) {
        logger = log;
    }

    void arm() {
        systemArmed = true;
        if (logger) logger->info("Detection system armed");
    }

    void disarm() {
        systemArmed = false;
        if (logger) logger->info("Detection system disarmed");
    }

    bool isArmed() const {
        return systemArmed;
    }

    // Motion detection
    void onMotionDetected(const std::string& location) {
        if (!systemArmed) return;

        Detection detection(DetectionType::MOTION, location);
        detections.push_back(detection);

        if (logger) {
            logger->logDetection("Motion detected at " + location);
        }
    }

    // Smoke detection
    void onSmokeDetected(const std::string& location) {
        if (!systemArmed) return;

        Detection detection(DetectionType::SMOKE, location);
        detections.push_back(detection);

        if (logger) {
            logger->critical("SMOKE DETECTED at " + location + " - Emergency alert!");
        }
    }

    // Gas detection
    void onGasDetected(const std::string& location) {
        if (!systemArmed) return;

        Detection detection(DetectionType::GAS, location);
        detections.push_back(detection);

        if (logger) {
            logger->critical("GAS DETECTED at " + location + " - Emergency alert!");
        }
    }

    // Intrusion detection
    void onIntrusionDetected(const std::string& location) {
        if (!systemArmed) return;

        Detection detection(DetectionType::INTRUSION, location);
        detections.push_back(detection);

        if (logger) {
            logger->critical("INTRUSION DETECTED at " + location + " - Security alert!");
        }
    }

    // Get active detections
    std::vector<Detection> getActiveDetections() const {
        std::vector<Detection> active;
        for (const auto& det : detections) {
            if (det.isActive) {
                active.push_back(det);
            }
        }
        return active;
    }

    // Clear a detection
    void clearDetection(size_t index) {
        if (index < detections.size()) {
            detections[index].isActive = false;
            if (logger) {
                logger->info("Detection cleared: " + detections[index].location);
            }
        }
    }

    // Clear all detections
    void clearAllDetections() {
        for (auto& det : detections) {
            det.isActive = false;
        }
        if (logger) {
            logger->info("All detections cleared");
        }
    }

    std::string detectionTypeToString(DetectionType type) const {
        switch (type) {
        case DetectionType::MOTION:
            return "Motion";
        case DetectionType::SMOKE:
            return "Smoke";
        case DetectionType::GAS:
            return "Gas";
        case DetectionType::INTRUSION:
            return "Intrusion";
        default:
            return "Unknown";
        }
    }
};
