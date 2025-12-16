#ifndef ALARMSYSTEM_H
#define ALARMSYSTEM_H

#include <thread>
#include <chrono>
#include <atomic>
#include <functional>
#include <iostream>
#include <string>
#include "Logger.h"

class AlarmSystem {
private:
    std::atomic<bool> isActive;          // Flag indicating if alarm is active / علم يشير إلى تنشيط الإنذار
    std::atomic<bool> isAcknowledged;    // Flag for user acknowledgment / علم لإقرار المستخدم
    std::thread alarmThread;             // Thread for running alarm / خيط لتشغيل الإنذار
    Logger& logger;                      // Reference to logger / مرجع للمسجل
    
    void runAlarm(int durationSeconds, const std::string& alarmType); // Run alarm for specified duration / تشغيل الإنذار لمدة محددة
    void triggerLights(bool turnOn);     // Control lights during alarm / التحكم بالأضواء أثناء الإنذار
    
public:
    AlarmSystem();                       // Constructor / المُنشئ
    ~AlarmSystem();                      // Destructor / المُدمِّر
    
    // Activate motion alarm (5 seconds) / تفعيل إنذار الحركة (5 ثواني)
    void activateMotionAlarm();
    
    // Activate smoke alarm (10 seconds) / تفعيل إنذار الدخان (10 ثواني)
    void activateSmokeAlarm();
    
    // Manually stop alarm / إيقاف الإنذار يدوياً
    void acknowledgeAlarm();
    
    // Check alarm status / التحقق من حالة الإنذار
    bool isAlarmActive() const;
    
    // Stop all alarms / إيقاف جميع الإنذارات
    void stopAllAlarms();
};
