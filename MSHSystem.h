#pragma once

#include <string>
#include <memory>
#include "ModeSubsystem_Bashir/Mode.h"
#include "state/State.h"
#include "modules/devices/DeviceManager.h"
#include "Logger.h"
#include "DetectionSystem.h"

enum class SystemMode {
    Normal,
    Evening,
    Party,
    Cinema
};

enum class SystemState {
    Normal,
    Sleep,
    HighPerformance
};

class MSHSystem {
public:
    MSHSystem();
    void run();

    // Device management
    DeviceManager& getDeviceManager() { return deviceManager; }
    const DeviceManager& getDeviceManager() const { return deviceManager; }

    // Logger and Detection
    Logger& getLogger() { return logger; }
    DetectionSystem& getDetectionSystem() { return detectionSystem; }

    // Mode and State control
    void setMode(SystemMode mode);
    void setState(SystemState state);
    SystemMode getCurrentMode() const { return currentMode; }
    SystemState getCurrentState() const { return currentState; }

    // Helper functions for modes to control devices
    void setAllLights(bool on) { deviceManager.setAllLights(on); }
    void setAllCameras(bool on) { deviceManager.setAllCameras(on); }
    void setAllTVs(bool on) { deviceManager.setAllTVs(on); }
    void setAllMusicSystems(bool on) { deviceManager.setAllMusicSystems(on); }
    void setAllSmokeGasDetectors(bool on) { deviceManager.setAllSmokeGasDetectors(on); }

    // State-specific control
    void setCameraPerformance(const std::string& level);
    void setLightMode(const std::string& mode);
    void setPowerSaving(bool enabled);
    void turnOffNonEssentialDevices();

private:
    void displayMainMenu();
    void handleUserSelection(int selection);
    void showHomeStatus() const;
    void addDevice();
    void removeDevice();
    void controlDevice();
    void changeMode();
    void changeState();
    void showManual() const;
    void showAbout() const;

    DeviceManager deviceManager;
    SystemMode currentMode;
    SystemState currentState;
    std::string cameraPerformance;
    std::string lightMode;
    bool powerSaving;
    Logger logger;
    DetectionSystem detectionSystem;
};
