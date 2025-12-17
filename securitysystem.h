#ifndef SECURITYSYSTEM_H
#define SECURITYSYSTEM_H

#include <vector>
#include <memory>
#include <string>
#include "Device.h"
#include "alarmsystem.h"
#include "Logger.h"

// Forward declarations for device types
class Camera;
class SmokeGasDetector;

class SecuritySystem {
private:
    std::vector<std::shared_ptr<Camera>> cameras;           // List of cameras
    std::vector<std::shared_ptr<SmokeGasDetector>> detectors; // List of detectors
    AlarmSystem alarmSystem;               // Alarm system instance
    Logger logger;                        // Logger instance
    bool isSecurityActive;                 // Security system status
    
public:
    SecuritySystem();                      // Constructor
    
    // Device management
    void addCamera(std::shared_ptr<Camera> camera);
    void addDetector(std::shared_ptr<SmokeGasDetector> detector);
    
    // Security control
    void activateSecurity();
    void deactivateSecurity();
    bool isActive() const;
    
    // Event detection
    void checkForMotion();                 // Check for motion / التحقق من الحركة
    void checkForSmoke();                  // Check for smoke
    
    // Simulation functions
    void simulateMotionDetection(int cameraId = 1); // Simulate motion
    void simulateSmokeDetection(int detectorId = 1); // Simulate smoke
    
    // Emergency response
    void callPolice();                     // Call police
};

#endif