#ifndef SECURITYSYSTEM_H
#define SECURITYSYSTEM_H

#include <vector>
#include <memory>
#include <string>
#include "Device.h"
#include "AlarmSystem.h"
#include "Logger.h"

class SecuritySystem {
private:
    std::vector<std::shared_ptr<Camera>> cameras;           // List of cameras / قائمة الكاميرات
    std::vector<std::shared_ptr<SmokeGasDetector>> detectors; // List of detectors / قائمة الكواشف
    AlarmSystem alarmSystem;               // Alarm system instance / مثيل نظام الإنذار
    Logger& logger;                        // Logger reference / مرجع المسجل
    bool isSecurityActive;                 // Security system status / حالة النظام الأمني
    
public:
    SecuritySystem();                      // Constructor / المُنشئ
    
    // Device management / إدارة الأجهزة
    void addCamera(std::shared_ptr<Camera> camera);
    void addDetector(std::shared_ptr<SmokeGasDetector> detector);
    
    // Security control / التحكم بالأمان
    void activateSecurity();
    void deactivateSecurity();
    bool isActive() const;
    
    // Event detection / كشف الأحداث
    void checkForMotion();                 // Check for motion / التحقق من الحركة
    void checkForSmoke();                  // Check for smoke / التحقق من الدخان
    
    // Simulation functions / دوال المحاكاة
    void simulateMotionDetection(int cameraId = 1); // Simulate motion / محاكاة الحركة
    void simulateSmokeDetection(int detectorId = 1); // Simulate smoke / محاكاة الدخان
    
    // Emergency response / الاستجابة للطوارئ
    void callPolice();                     // Call police / الاتصال بالشرطة
};

#endif