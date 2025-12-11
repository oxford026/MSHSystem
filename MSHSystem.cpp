#include "MSHSystem.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>

MSHSystem::MSHSystem()
    : currentMode(SystemMode::Normal),
      currentState(SystemState::Normal) {}

// Helper functions to convert enums to string
static std::string modeToString(SystemMode mode)
{
    switch (mode)
    {
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

static std::string stateToString(SystemState state)
{
    switch (state)
    {
    case SystemState::Normal:
        return "Normal";
    case SystemState::Sleep:
        return "Sleep";
    case SystemState::HighPerformance:
        return "High Performance";
    }
    return "Unknown";
}

void MSHSystem::showHomeStatus() const
{
    std::cout << "\n=== HOME STATUS ===\n";
    std::cout << "Current Mode : " << modeToString(currentMode) << "\n";
    std::cout << "Current State: " << stateToString(currentState) << "\n";

    std::cout << "\nDevices:\n";
    std::cout << "  (No devices registered yet - device subsystem integration pending.)\n";

    std::cout << "\nPress Enter to return to the main menu...\n";
    std::cin.get();
}

void MSHSystem::run()
{
    while (true)
    {
        displayMainMenu();

        int choice;
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid selection. Please enter a number.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        handleUserSelection(choice);
    }
}

void MSHSystem::displayMainMenu()
{
    std::cout << "\n=== My Sweet Home System ===\n";
    std::cout << "1. Get Home Status\n";
    std::cout << "2. Add Device\n";
    std::cout << "3. Remove Device\n";
    std::cout << "4. Power On Device\n";
    std::cout << "5. Power Off Device\n";
    std::cout << "6. Change Mode\n";
    std::cout << "7. Change State\n";
    std::cout << "8. Manual\n";
    std::cout << "9. About\n";
    std::cout << "0. Exit\n";
    std::cout << "Select: ";
}

void MSHSystem::handleUserSelection(int selection)
{
    switch (selection)
    {
    case 0:
        std::cout << "Exiting...\n";
        std::exit(0);

    case 1:
        showHomeStatus();
        break;

    case 8:
        std::cout << "\n=== MANUAL ===\n";
        std::cout << "Use the menu numbers to navigate.\n";
        std::cout << "1: View home status\n";
        std::cout << "2: Add new devices\n";
        std::cout << "3: Remove devices\n";
        std::cout << "4/5: Power devices on/off\n";
        std::cout << "6: Change system mode\n";
        std::cout << "7: Change performance state\n";
        std::cout << "9: View system information\n";
        std::cout << "Press Enter to return to the main menu...\n";
        std::cin.get();
        break;

    case 9:
        std::cout << "\n=== ABOUT ===\n";
        std::cout << "My Sweet Home System (MSH)\n";
        std::cout << "Controller: MSHSystem (Mahmoud Jalloh)\n";
        std::cout << "This module handles the main menu and integrates all subsystems.\n";
        std::cout << "Press Enter to return to the main menu...\n";
        std::cin.get();
        break;

    default:
        std::cout << "Option not implemented yet.\n";
        break;
    }
}
