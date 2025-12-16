#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iostream>

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Logger {
private:
    std::ofstream logFile;
    LogLevel minLevel;
    bool consoleOutput;

    std::string levelToString(LogLevel level) const {
        switch (level) {
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARNING:
            return "WARNING";
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::CRITICAL:
            return "CRITICAL";
        default:
            return "UNKNOWN";
        }
    }

    std::string getCurrentTime() const {
        time_t now = time(nullptr);
        struct tm* timeinfo = localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        return std::string(buffer);
    }

    void writeLog(LogLevel level, const std::string& message) {
        if (level < minLevel) return;

        std::string timestamp = getCurrentTime();
        std::string levelStr = levelToString(level);
        std::string logEntry = "[" + timestamp + "] [" + levelStr + "] " + message;

        // Write to file
        if (logFile.is_open()) {
            logFile << logEntry << "\n";
            logFile.flush();
        }

        // Write to console if enabled
        if (consoleOutput) {
            std::cout << logEntry << "\n";
        }
    }

public:
    Logger() : minLevel(LogLevel::INFO), consoleOutput(true) {
        // Optionally open log file
        logFile.open("msh_system.log", std::ios::app);
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void setLogLevel(LogLevel level) {
        minLevel = level;
    }

    void setConsoleOutput(bool enabled) {
        consoleOutput = enabled;
    }

    void debug(const std::string& message) {
        writeLog(LogLevel::DEBUG, message);
    }

    void info(const std::string& message) {
        writeLog(LogLevel::INFO, message);
    }

    void warning(const std::string& message) {
        writeLog(LogLevel::WARNING, message);
    }

    void error(const std::string& message) {
        writeLog(LogLevel::ERROR, message);
    }

    void critical(const std::string& message) {
        writeLog(LogLevel::CRITICAL, message);
    }

    // Device-specific logging
    void logDeviceAction(const std::string& deviceName, const std::string& action) {
        info("Device [" + deviceName + "]: " + action);
    }

    void logModeChange(const std::string& modeName) {
        info("System mode changed to: " + modeName);
    }

    void logStateChange(const std::string& stateName) {
        info("System state changed to: " + stateName);
    }

    void logDetection(const std::string& detectionType) {
        warning("Detection alert: " + detectionType);
    }

    void logError(const std::string& errorMessage) {
        error("System error: " + errorMessage);
    }
};
