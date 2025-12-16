#include "SecuritySystem.h"
#include <iostream>

// Constructor implementation / تنفيذ المُنشئ
SecuritySystem::SecuritySystem() 
    : isSecurityActive(false), logger(Logger::getInstance()) {
    std::cout << "Security System Initialized / تم تهيئة النظام الأمني" << std::endl;
}

// Check for motion detection / التحقق من كشف الحركة
void SecuritySystem::checkForMotion() {
    if (!isSecurityActive) return; // Return if security inactive / العودة إذا كان النظام الأمني غير نشط
    
    // Check all cameras / التحقق من جميع الكاميرات
    for (auto& camera : cameras) {
        if (camera->isOn() && camera->detectMotion()) {
            std::cout << "\n🚨 MOTION DETECTED by Camera / تم اكتشاف حركة بواسطة الكاميرا " 
                      << camera->getId() << std::endl;
            
            // Activate motion alarm / تفعيل إنذار الحركة
            alarmSystem.activateMotionAlarm();
            
            // Log the event (Lights triggered in AlarmSystem) / تسجيل الحدث (الأضواء تشتغل في نظام الإنذار)
            
            // Call police / الاتصال بالشرطة
            callPolice();
            
            // Log event / تسجيل الحدث
            logger.log("SECURITY", "Motion detected by Camera / تم اكتشاف حركة بواسطة الكاميرا " + 
                       std::to_string(camera->getId()), "SUCCESS");
            break; // Stop after first detection / التوقف بعد أول اكتشاف
        }
    }
}

// Check for smoke detection / التحقق من كشف الدخان
void SecuritySystem::checkForSmoke() {
    // Check all detectors (always active) / التحقق من جميع الكواشف (دائماً نشطة)
    for (auto& detector : detectors) {
        if (detector->isOn() && detector->detectSmoke()) {
            std::cout << "\n🔥 SMOKE DETECTED by Detector / تم اكتشاف دخان بواسطة الكاشف " 
                      << detector->getId() << std::endl;
            
            // Activate smoke alarm / تفعيل إنذار الدخان
            alarmSystem.activateSmokeAlarm();
            
            // Log event / تسجيل الحدث
            logger.log("SECURITY", "Smoke detected by Detector / تم اكتشاف دخان بواسطة الكاشف " + 
                       std::to_string(detector->getId()), "SUCCESS");
            break; // Stop after first detection / التوقف بعد أول اكتشاف
        }
    }
}

// Simulate motion detection / محاكاة كشف الحركة
void SecuritySystem::simulateMotionDetection(int cameraId) {
    std::cout << "\n🔍 Simulating motion detection... / محاكاة اكتشاف الحركة..." << std::endl;
    
    // Find and simulate camera / البحث عن الكاميرا ومحاكاتها
    for (auto& camera : cameras) {
        if (camera->getId() == cameraId) {
            camera->setMotionDetected(true);  // Set motion detected / تعيين اكتشاف الحركة
            checkForMotion();                 // Trigger security check / تشغيل التحقق الأمني
            camera->setMotionDetected(false); // Reset / إعادة تعيين
            return;
        }
    }
    std::cout << "Camera / الكاميرا " << cameraId << " not found! / غير موجودة!" << std::endl;
}

// Simulate smoke detection / محاكاة كشف الدخان
void SecuritySystem::simulateSmokeDetection(int detectorId) {
    std::cout << "\n💨 Simulating smoke detection... / محاكاة اكتشاف الدخان..." << std::endl;
    
    // Find and simulate detector / البحث عن الكاشف ومحاكاته
    for (auto& detector : detectors) {
        if (detector->getId() == detectorId) {
            detector->setSmokeDetected(true);  // Set smoke detected / تعيين اكتشاف الدخان
            checkForSmoke();                   // Trigger security check / تشغيل التحقق الأمني
            detector->setSmokeDetected(false); // Reset / إعادة تعيين
            return;
        }
    }
    std::cout << "Detector / الكاشف " << detectorId << " not found! / غير موجود!" << std::endl;
}

// Call police simulation / محاكاة الاتصال بالشرطة
void SecuritySystem::callPolice() {
    std::cout << "📞 A call is placed to Police / تم إجراء اتصال بالشرطة" << std::endl;
    logger.log("SECURITY", "Police called / تم الاتصال بالشرطة", "SUCCESS");
}