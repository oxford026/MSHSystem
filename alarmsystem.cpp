
#include "alarmsystem.h"
#include "MSHSystem.h"
#include <iostream>
#include <memory>

// Global MSHSystem instance (assumed)
extern MSHSystem* globalMSHSystem;

// Constructor implementation
AlarmSystem::AlarmSystem()
    : isActive(false), isAcknowledged(false), logger() {
    std::cout << "Alarm System Initialized" << std::endl;
}

// Destructor implementation
AlarmSystem::~AlarmSystem() {
    stopAllAlarms(); // Stop any running alarms
    if (alarmThread.joinable()) {
        alarmThread.join(); // Wait for thread to finish
    }
}

// Run alarm for specified duration
void AlarmSystem::runAlarm(int durationSeconds, const std::string& alarmType) {
    isActive = true;
    isAcknowledged = false;
    
    std::cout << "\n🚨 ALARM ACTIVATED / تم تفعيل الإنذار: " << alarmType << " alarm for " 
              << durationSeconds << " seconds!" << std::endl;
    
    // Turn on lights for motion alarm
    if (alarmType == "MOTION") {
        triggerLights(true);
    }
    
    // Log the event
    logger.info(alarmType + " alarm started");
    
    // Start timing the alarm / بدء توقيت الإنذار
    auto startTime = std::chrono::steady_clock::now();
    
    // Main alarm loop / الحلقة الرئيسية للإنذار
    while (isActive) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>
                              (currentTime - startTime).count();
        
        // Stop if user acknowledged
        if (isAcknowledged) {
            std::cout << "⚠️ Alarm acknowledged by user - Stopping early" << std::endl;
            logger.info(alarmType + " alarm acknowledged by user");
            break;
        }
        
        // Stop after duration elapsed / التوقف بعد انتهاء المدة
        if (elapsedSeconds >= durationSeconds) {
            break;
        }
        
        // Alarm sound simulation
        std::cout << "BEEP! ";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    // Turn off lights after alarm
    if (alarmType == "MOTION") {
        triggerLights(false);
    }
    
    isActive = false;
    std::cout << "\n✅ Alarm stopped" << std::endl;
    logger.info(alarmType + " alarm stopped");
}

// Control lights during alarm
void AlarmSystem::triggerLights(bool turnOn) {
    if (!globalMSHSystem) return; // Safety check
    
    const auto& devices = globalMSHSystem->getDeviceManager().getAllDevices();
    int lightsTriggered = 0; // Counter for triggered lights
    
    // Loop through all devices and handle Lights only
    for (auto& device : devices) {
        auto light = std::dynamic_pointer_cast<Light>(device);
        if (light) {
            if (turnOn) {
                light->turnOn();
                lightsTriggered++;
            } else {
                light->turnOff();
            }
        }
    }
    
    // Print status message
    if (turnOn && lightsTriggered > 0) {
        std::cout << "💡 " << lightsTriggered << " lights turned ON for alarm" << std::endl;
    }
}

// Activate motion alarm (5 seconds) / تفعيل إنذار الحركة (5 ثواني)
void AlarmSystem::activateMotionAlarm() {
    if (isActive) {
        std::cout << "⚠️ Another alarm is already active" << std::endl;
        return;
    }
    
    // Run alarm in separate thread / تشغيل الإنذار في خيط منفصل
    alarmThread = std::thread(&AlarmSystem::runAlarm, this, 5, "MOTION");
    alarmThread.detach(); // Detach to run in background
}

// Activate smoke alarm (10 seconds) / تفعيل إنذار الدخان (10 ثواني)
void AlarmSystem::activateSmokeAlarm() {
    if (isActive) {
        std::cout << "⚠️ Another alarm is already active" << std::endl;
        return;
    }
    
    std::cout << "\n🔥 SMOKE DETECTED! Press any key to acknowledge alarm..." << std::endl;
    
    // Run smoke alarm / تشغيل إنذار الدخان
    alarmThread = std::thread(&AlarmSystem::runAlarm, this, 10, "SMOKE");
    alarmThread.detach(); // Detach thread
}

// Manually acknowledge/stop alarm
void AlarmSystem::acknowledgeAlarm() {
    if (isActive && !isAcknowledged) {
        isAcknowledged = true;
        std::cout << "✅ Alarm acknowledged" << std::endl;
    }
}

// Check if alarm is active
bool AlarmSystem::isAlarmActive() const {
    return isActive;
}

// Stop all alarms
void AlarmSystem::stopAllAlarms() {
    isActive = false;
    isAcknowledged = true;
}