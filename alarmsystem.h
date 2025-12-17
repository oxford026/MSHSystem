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
    std::atomic<bool> isActive;          // Flag indicating if alarm is active
    std::atomic<bool> isAcknowledged;    // Flag for user acknowledgment
    std::thread alarmThread;             // Thread for running alarm
    Logger logger;                       // Logger instance

    void runAlarm(int durationSeconds, const std::string& alarmType); // Run alarm for specified duration
    void triggerLights(bool turnOn);     // Control lights during alarm
    
public:
    AlarmSystem();                       // Constructor
    ~AlarmSystem();                      // Destructor

    // Activate motion alarm (5 seconds)
    void activateMotionAlarm();
    
    // Activate smoke alarm (10 seconds)
    void activateSmokeAlarm();
    
    // Manually stop alarm
    void acknowledgeAlarm();
    
    // Check alarm status
    bool isAlarmActive() const;
    
    // Stop all alarms
    void stopAllAlarms();
};

#endif
