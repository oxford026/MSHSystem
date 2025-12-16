
#include "AlarmSystem.h"
#include "MSHSystem.h"
#include <iostream>

// Global MSHSystem instance (assumed) / مثيل عام لنظام MSH (مفترض)
extern MSHSystem* globalMSHSystem;

// Constructor implementation / تنفيذ المُنشئ
AlarmSystem::AlarmSystem() 
    : isActive(false), isAcknowledged(false), logger(Logger::getInstance()) {
    std::cout << "Alarm System Initialized / تم تهيئة نظام الإنذار" << std::endl;
}

// Destructor implementation / تنفيذ المُدمِّر
AlarmSystem::~AlarmSystem() {
    stopAllAlarms(); // Stop any running alarms / إيقاف أي إنذارات قيد التشغيل
    if (alarmThread.joinable()) {
        alarmThread.join(); // Wait for thread to finish / انتظار انتهاء الخيط
    }
}

// Run alarm for specified duration / تشغيل الإنذار لمدة محددة
void AlarmSystem::runAlarm(int durationSeconds, const std::string& alarmType) {
    isActive = true;
    isAcknowledged = false;
    
    std::cout << "\n🚨 ALARM ACTIVATED / تم تفعيل الإنذار: " << alarmType << " alarm for " 
              << durationSeconds << " seconds!" << std::endl;
    
    // Turn on lights for motion alarm / تشغيل الأضواء في حالة إنذار الحركة
    if (alarmType == "MOTION") {
        triggerLights(true);
    }
    
    // Log the event / تسجيل الحدث
    logger.log("ALARM", alarmType + " alarm started / إنذار " + alarmType + " بدأ", "SUCCESS");
    
    // Start timing the alarm / بدء توقيت الإنذار
    auto startTime = std::chrono::steady_clock::now();
    
    // Main alarm loop / الحلقة الرئيسية للإنذار
    while (isActive) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>
                              (currentTime - startTime).count();
        
        // Stop if user acknowledged / التوقف إذا أقر المستخدم
        if (isAcknowledged) {
            std::cout << "⚠️ Alarm acknowledged by user - Stopping early / تم إقرار الإنذار من قبل المستخدم - إيقاف مبكر" << std::endl;
            logger.log("ALARM", alarmType + " alarm acknowledged by user / تم إقرار إنذار " + alarmType + " من قبل المستخدم", "SUCCESS");
            break;
        }
        
        // Stop after duration elapsed / التوقف بعد انتهاء المدة
        if (elapsedSeconds >= durationSeconds) {
            break;
        }
        
        // Alarm sound simulation / محاكاة صوت الإنذار
        std::cout << "BEEP! ";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    // Turn off lights after alarm / إطفاء الأضواء بعد الإنذار
    if (alarmType == "MOTION") {
        triggerLights(false);
    }
    
    isActive = false;
    std::cout << "\n✅ Alarm stopped / تم إيقاف الإنذار" << std::endl;
    logger.log("ALARM", alarmType + " alarm stopped / إنذار " + alarmType + " توقف", "SUCCESS");
}

// Control lights during alarm / التحكم بالأضواء أثناء الإنذار
void AlarmSystem::triggerLights(bool turnOn) {
    if (!globalMSHSystem) return; // Safety check / فحص السلامة
    
    auto& devices = globalMSHSystem->getAllDevices();
    int lightsTriggered = 0; // Counter for triggered lights / عداد للأضواء المشغلة
    
    // Loop through all devices / التكرار عبر جميع الأجهزة
    for (auto& device : devices) {
        if (device->getType() == "LIGHT" && device->isOperational()) {
            if (turnOn) {
                device->turnOn();
                lightsTriggered++;
            } else {
                device->turnOff();
            }
        }
    }
    
    // Print status message / طباعة رسالة الحالة
    if (turnOn && lightsTriggered > 0) {
        std::cout << "💡 " << lightsTriggered << " lights turned ON for alarm / تم تشغيل " << lightsTriggered << " أضواء للإنذار" << std::endl;
    }
}

// Activate motion alarm (5 seconds) / تفعيل إنذار الحركة (5 ثواني)
void AlarmSystem::activateMotionAlarm() {
    if (isActive) {
        std::cout << "⚠️ Another alarm is already active / إنذار آخر نشط بالفعل" << std::endl;
        return;
    }
    
    // Run alarm in separate thread / تشغيل الإنذار في خيط منفصل
    alarmThread = std::thread(&AlarmSystem::runAlarm, this, 5, "MOTION");
    alarmThread.detach(); // Detach to run in background / فصل للعمل في الخلفية
}

// Activate smoke alarm (10 seconds) / تفعيل إنذار الدخان (10 ثواني)
void AlarmSystem::activateSmokeAlarm() {
    if (isActive) {
        std::cout << "⚠️ Another alarm is already active / إنذار آخر نشط بالفعل" << std::endl;
        return;
    }
    
    std::cout << "\n🔥 SMOKE DETECTED! Press any key to acknowledge alarm... / تم اكتشاف دخان! اضغط أي مفتاح لإقرار الإنذار..." << std::endl;
    
    // Run smoke alarm / تشغيل إنذار الدخان
    alarmThread = std::thread(&AlarmSystem::runAlarm, this, 10, "SMOKE");
    alarmThread.detach(); // Detach thread / فصل الخيط
}

// Manually acknowledge/stop alarm / الإقرار اليدوي/إيقاف الإنذار
void AlarmSystem::acknowledgeAlarm() {
    if (isActive && !isAcknowledged) {
        isAcknowledged = true;
        std::cout << "✅ Alarm acknowledged / تم إقرار الإنذار" << std::endl;
    }
}

// Check if alarm is active / التحقق مما إذا كان الإنذار نشطاً
bool AlarmSystem::isAlarmActive() const {
    return isActive;
}

// Stop all alarms / إيقاف جميع الإنذارات
void AlarmSystem::stopAllAlarms() {
    isActive = false;
    isAcknowledged = true;
}