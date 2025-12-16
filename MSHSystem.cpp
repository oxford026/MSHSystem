#include "MSHSystem.h"
#include "ModeSubsystem_Bashir/NormalMode.h"
#include "ModeSubsystem_Bashir/EveningMode.h"
#include "ModeSubsystem_Bashir/PartyMode.h"
#include "ModeSubsystem_Bashir/CinemaMode.h"
#include "state/NormalState.h"
#include "state/SleepState.h"
#include "state/HighPerformanceState.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>

// In MSHSystem class add / ✅ MSHSystem class 
// Add these includes at the top if not already there
#include "AlarmSystem.h"
#include "SecuritySystem.h"

MSHSystem::MSHSystem()
    : currentMode(SystemMode::Normal),
      currentState(SystemState::Normal),
      cameraPerformance("NORMAL"),
      lightMode("NORMAL"),
      powerSaving(false) {
    // Initialize detection system with logger
    detectionSystem.setLogger(&logger);
    logger.info("MSHSystem initialized successfully");
}

// Helper functions to convert enums to string
static std::string modeToString(SystemMode mode) {
    switch (mode) {
    case SystemMode::Normal:
        return "Normal";
    case SystemMode::Evening:
        return "Evening";
    case SystemMode::Party:
        return "Party";
    case SystemMode::Cinema:
        return "Cinema";
    }
    return "Unknown";
}

static std::string stateToString(SystemState state) {
    switch (state) {
    case SystemState::Normal:
        return "Normal";
    case SystemState::Sleep:
        return "Sleep";
    case SystemState::HighPerformance:
        return "High Performance";
    }
    return "Unknown";
}

void MSHSystem::setMode(SystemMode mode) {
    currentMode = mode;
    std::cout << "Mode changed to: " << modeToString(mode) << "\n";
    logger.logModeChange(modeToString(mode));
}

void MSHSystem::setState(SystemState state) {
    currentState = state;
    std::cout << "State changed to: " << stateToString(state) << "\n";
    logger.logStateChange(stateToString(state));
}

void MSHSystem::setCameraPerformance(const std::string& level) {
    cameraPerformance = level;
}

void MSHSystem::setLightMode(const std::string& mode) {
    lightMode = mode;
}

void MSHSystem::setPowerSaving(bool enabled) {
    powerSaving = enabled;
}

void MSHSystem::turnOffNonEssentialDevices() {
    deviceManager.setAllLights(false);
    deviceManager.setAllTVs(false);
    deviceManager.setAllMusicSystems(false);
}

// In MSHSystem.cpp add these functions / ✅ MSHSystem.cpp : 
// Handle user alarm acknowledgment / 
void MSHSystem::handleAlarmAcknowledgment() {
    alarmSystem.acknowledgeAlarm();
}

// Check if alarm is active / 
bool MSHSystem::isAlarmActive() const {
    return alarmSystem.isAlarmActive();
}

// Simulate motion event / 
void MSHSystem::simulateMotionEvent() {
    securitySystem.simulateMotionDetection();
}

// Simulate smoke event / 
void MSHSystem::simulateSmokeEvent() {
    securitySystem.simulateSmokeDetection();
}

void MSHSystem::showHomeStatus() const {
    std::cout << "\n=== HOME STATUS ===\n";
    std::cout << "Current Mode : " << modeToString(currentMode) << "\n";
    std::cout << "Current State: " << stateToString(currentState) << "\n";
    std::cout << "Camera Performance: " << cameraPerformance << "\n";
    std::cout << "Light Mode: " << lightMode << "\n";
    std::cout << "Power Saving: " << (powerSaving ? "ON" : "OFF") << "\n";

    std::cout << "\nDevices (" << deviceManager.getDeviceCount() << " total):\n";
    const auto& devices = deviceManager.getAllDevices();
    if (devices.empty()) {
        std::cout << "  No devices registered.\n";
    } else {
        for (const auto& device : devices) {
            std::cout << "  ID " << device->getId() << ": " << device->getInfo();
            std::cout << " [" << (device->isOn_status() ? "ON" : "OFF") << "]\n";
        }
    }

    std::cout << "\nPress Enter to return to the main menu...\n";
    std::cin.get();
}

void MSHSystem::addDevice() {
    std::cout << "\n=== ADD DEVICE ===\n";
    std::cout << "Device Types:\n";
    std::cout << "1. Light\n";
    std::cout << "2. Camera\n";
    std::cout << "3. TV\n";
    std::cout << "4. Smoke & Gas Detector\n";
    std::cout << "5. Music System\n";
    std::cout << "Select type: ";

    int type;
    std::cin >> type;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter device name: ";
    std::string name;
    std::getline(std::cin, name);

    switch (type) {
    case 1: {
        std::cout << "Enter brightness (0-100) [default 50]: ";
        int brightness = 50;
        std::string input;
        std::getline(std::cin, input);
        if (!input.empty()) brightness = std::stoi(input);
        deviceManager.createLight(name, brightness);
        std::cout << "Light added successfully!\n";
        logger.logDeviceAction(name, "Light device added with brightness " + std::to_string(brightness));
        break;
    }
    case 2: {
        std::cout << "Enter FPS [default 30]: ";
        int fps = 30;
        std::string input;
        std::getline(std::cin, input);
        if (!input.empty()) fps = std::stoi(input);
        deviceManager.createCamera(name, fps);
        std::cout << "Camera added successfully!\n";
        logger.logDeviceAction(name, "Camera device added with FPS " + std::to_string(fps));
        break;
    }
    case 3: {
        std::cout << "Enter brand [default Generic]: ";
        std::string brand;
        std::getline(std::cin, brand);
        if (brand.empty()) brand = "Generic";
        deviceManager.createTV(name, brand);
        std::cout << "TV added successfully!\n";
        logger.logDeviceAction(name, "TV device added - Brand: " + brand);
        break;
    }
    case 4: {
        std::cout << "Enter sensitivity (1-10) [default 5]: ";
        int sensitivity = 5;
        std::string input;
        std::getline(std::cin, input);
        if (!input.empty()) sensitivity = std::stoi(input);
        deviceManager.createSmokeGasDetector(name, sensitivity);
        std::cout << "Detector added successfully!\n";
        logger.logDeviceAction(name, "Smoke & Gas Detector added with sensitivity " + std::to_string(sensitivity));
        break;
    }
    case 5: {
        std::cout << "Enter volume (0-100) [default 15]: ";
        int volume = 15;
        std::string input;
        std::getline(std::cin, input);
        if (!input.empty()) volume = std::stoi(input);
        deviceManager.createMusicSystem(name, volume);
        std::cout << "Music System added successfully!\n";
        logger.logDeviceAction(name, "Music System added with volume " + std::to_string(volume));
        break;
    }
    default:
        std::cout << "Invalid device type.\n";
    }

    std::cout << "Press Enter to continue...\n";
    std::cin.get();
}

void MSHSystem::removeDevice() {
    std::cout << "\n=== REMOVE DEVICE ===\n";
    const auto& devices = deviceManager.getAllDevices();
    if (devices.empty()) {
        std::cout << "No devices to remove.\n";
        std::cout << "Press Enter to continue...\n";
        std::cin.get();
        return;
    }

    std::cout << "Available devices:\n";
    for (const auto& device : devices) {
        std::cout << "ID " << device->getId() << ": " << device->getInfo() << "\n";
    }

    std::cout << "Enter device ID to remove: ";
    int id;
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (deviceManager.removeDevice(id)) {
        std::cout << "Device removed successfully!\n";
        logger.info("Device with ID " + std::to_string(id) + " removed from system");
    } else {
        std::cout << "Device not found.\n";
        logger.warning("Attempt to remove non-existent device with ID " + std::to_string(id));
    }

    std::cout << "Press Enter to continue...\n";
    std::cin.get();
}

void MSHSystem::controlDevice() {
    std::cout << "\n=== CONTROL DEVICE ===\n";
    const auto& devices = deviceManager.getAllDevices();
    if (devices.empty()) {
        std::cout << "No devices available.\n";
        std::cout << "Press Enter to continue...\n";
        std::cin.get();
        return;
    }

    std::cout << "Available devices:\n";
    for (const auto& device : devices) {
        std::cout << "ID " << device->getId() << ": " << device->getInfo() << " [" 
                  << (device->isOn_status() ? "ON" : "OFF") << "]\n";
    }

    std::cout << "Enter device ID: ";
    int id;
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto device = deviceManager.findDevice(id);
    if (!device) {
        std::cout << "Device not found.\n";
        std::cout << "Press Enter to continue...\n";
        std::cin.get();
        return;
    }

    std::cout << "Device: " << device->getInfo() << "\n";
    std::cout << "1. Turn ON\n";
    std::cout << "2. Turn OFF\n";
    std::cout << "Select: ";
    int action;
    std::cin >> action;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (action == 1) {
        device->turnOn();
        std::cout << "Device turned ON.\n";
        logger.logDeviceAction(device->getName(), "Turned ON");
    } else if (action == 2) {
        device->turnOff();
        std::cout << "Device turned OFF.\n";
        logger.logDeviceAction(device->getName(), "Turned OFF");
    }

    std::cout << "Press Enter to continue...\n";
    std::cin.get();
}

void MSHSystem::changeMode() {
    std::cout << "\n=== CHANGE MODE ===\n";
    std::cout << "Available Modes:\n";
    std::cout << "1. Normal\n";
    std::cout << "2. Evening\n";
    std::cout << "3. Party\n";
    std::cout << "4. Cinema\n";
    std::cout << "Select mode: ";

    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    SystemMode newMode;
    std::string modeName;

    switch (choice) {
    case 1:
        newMode = SystemMode::Normal;
        modeName = "Normal";
        deviceManager.setAllLights(false);
        deviceManager.setAllCameras(false);
        deviceManager.setAllSmokeGasDetectors(true);
        deviceManager.setAllTVs(false);
        deviceManager.setAllMusicSystems(false);
        break;
    case 2:
        newMode = SystemMode::Evening;
        modeName = "Evening";
        deviceManager.setAllLights(false);
        deviceManager.setAllCameras(true);
        deviceManager.setAllSmokeGasDetectors(true);
        deviceManager.setAllTVs(false);
        deviceManager.setAllMusicSystems(false);
        break;
    case 3:
        newMode = SystemMode::Party;
        modeName = "Party";
        deviceManager.setAllLights(true);
        deviceManager.setAllCameras(true);
        deviceManager.setAllSmokeGasDetectors(true);
        deviceManager.setAllTVs(false);
        deviceManager.setAllMusicSystems(true);
        break;
    case 4:
        newMode = SystemMode::Cinema;
        modeName = "Cinema";
        deviceManager.setAllLights(false);
        deviceManager.setAllCameras(true);
        deviceManager.setAllSmokeGasDetectors(true);
        deviceManager.setAllTVs(true);
        deviceManager.setAllMusicSystems(false);
        break;
    default:
        std::cout << "Invalid mode.\n";
        std::cout << "Press Enter to continue...\n";
        std::cin.get();
        return;
    }

    setMode(newMode);
    std::cout << "Mode changed to: " << modeName << "\nDevices updated accordingly.\n";
    std::cout << "Press Enter to continue...\n";
    std::cin.get();
}

void MSHSystem::changeState() {
    std::cout << "\n=== CHANGE STATE ===\n";
    std::cout << "Available States:\n";
    std::cout << "1. Normal\n";
    std::cout << "2. Sleep\n";
    std::cout << "3. High Performance\n";
    std::cout << "Select state: ";

    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    SystemState newState;
    std::string stateName;

    switch (choice) {
    case 1:
        newState = SystemState::Normal;
        stateName = "Normal";
        setCameraPerformance("NORMAL");
        setLightMode("NORMAL");
        setPowerSaving(false);
        break;
    case 2:
        newState = SystemState::Sleep;
        stateName = "Sleep";
        turnOffNonEssentialDevices();
        setCameraPerformance("SLEEP");
        setLightMode("OFF");
        setPowerSaving(true);
        break;
    case 3:
        newState = SystemState::HighPerformance;
        stateName = "High Performance";
        setCameraPerformance("HIGH");
        setLightMode("MAX");
        setPowerSaving(false);
        break;
    default:
        std::cout << "Invalid state.\n";
        std::cout << "Press Enter to continue...\n";
        std::cin.get();
        return;
    }

    setState(newState);
    std::cout << "State changed to: " << stateName << "\nSystem adjusted accordingly.\n";
    std::cout << "Press Enter to continue...\n";
    std::cin.get();
}

void MSHSystem::showManual() const {
    std::cout << "\n=== MANUAL ===\n";
    std::cout << "My Sweet Home System Controls:\n\n";
    std::cout << "1. Get Home Status - View current mode, state, and all connected devices\n";
    std::cout << "2. Add Device - Add a new device (Light, Camera, TV, Detector, Music System)\n";
    std::cout << "3. Remove Device - Remove a device by ID\n";
    std::cout << "4. Power On Device - Turn on a specific device\n";
    std::cout << "5. Power Off Device - Turn off a specific device\n";
    std::cout << "6. Change Mode - Switch between Normal, Evening, Party, Cinema modes\n";
    std::cout << "7. Change State - Switch between Normal, Sleep, High Performance states\n";
    std::cout << "8. Manual - Display this help message\n";
    std::cout << "9. About - View system information\n";
    std::cout << "0. Exit - Quit the application\n";
    std::cout << "\nPress Enter to return to the main menu...\n";
    std::cin.get();
}

void MSHSystem::showAbout() const {
    std::cout << "\n=== ABOUT ===\n";
    std::cout << "My Sweet Home System (MSH)\n";
    std::cout << "Version 2.0\n\n";
    std::cout << "System Features:\n";
    std::cout << "  - Multi-mode operation (Normal, Evening, Party, Cinema)\n";
    std::cout << "  - Performance states (Normal, Sleep, High Performance)\n";
    std::cout << "  - Device management and control\n";
    std::cout << "  - Automatic device synchronization with modes and states\n\n";
    std::cout << "Supported Devices:\n";
    std::cout << "  - Lights with brightness control\n";
    std::cout << "  - Cameras with FPS and night vision\n";
    std::cout << "  - TVs with brand and volume control\n";
    std::cout << "  - Smoke & Gas Detectors with sensitivity\n";
    std::cout << "  - Music Systems with volume control\n\n";
    std::cout << "Created by: TEAM MSH\n";
    std::cout << "Press Enter to return to the main menu...\n";
    std::cin.get();
}

void MSHSystem::run() {
    std::cout << "Welcome to My Sweet Home System!\n";
    while (true) {
        displayMainMenu();

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid selection. Please enter a number.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        handleUserSelection(choice);
    }
}

void MSHSystem::displayMainMenu() {
    std::cout << "\n=== My Sweet Home System ===\n";
    std::cout << "Current Mode: " << modeToString(currentMode) 
              << " | State: " << stateToString(currentState) << "\n";
    std::cout << "Devices: " << deviceManager.getDeviceCount() << "\n";
    std::cout << "\n1. Get Home Status\n";
    std::cout << "2. Add Device\n";
    std::cout << "3. Remove Device\n";
    std::cout << "4. Control Device\n";
    std::cout << "5. Change Mode\n";
    std::cout << "6. Change State\n";
    std::cout << "7. Manual\n";
    std::cout << "8. About\n";
    std::cout << "0. Exit\n";
    std::cout << "Select: ";
}

void MSHSystem::handleUserSelection(int selection) {
    switch (selection) {
    case 0:
        std::cout << "Thank you for using My Sweet Home System. Goodbye!\n";
        std::exit(0);

    case 1:
        showHomeStatus();
        break;

    case 2:
        addDevice();
        break;

    case 3:
        removeDevice();
        break;

    case 4:
        controlDevice();
        break;

    case 5:
        changeMode();
        break;

    case 6:
        changeState();
        break;

    case 7:
        showManual();
        break;

    case 8:
        showAbout();
        break;

    default:
        std::cout << "Invalid selection. Please try again.\n";
    }
}

// In mainMenu function add test option / ✅ mainMenu function
// Add this new function for testing alarms
void MSHSystem::testAlarmMenu() {
    std::cout << "\n=== Test Alarm System ===" << std::endl;
    std::cout << "1. Test Motion Alarm" << std::endl;
    std::cout << "2. Test Smoke Alarm" << std::endl;
    std::cout << "3. Acknowledge Alarm" << std::endl;
    std::cout << "Choice: ";

    char testChoice;
    std::cin >> testChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (testChoice == '1') {
        simulateMotionEvent();
    } else if (testChoice == '2') {
        simulateSmokeEvent();
    } else if (testChoice == '3') {
        handleAlarmAcknowledgment();
    } else {
        std::cout << "Invalid choice.\n";
    }