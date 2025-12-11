#pragma once

#include <string>

enum class SystemMode
{
    Normal,
    Evening,
    Party,
    Cinema
};

enum class SystemState
{
    Normal,
    Sleep,
    HighPerformance
};

class MSHSystem
{
public:
    MSHSystem();
    void run();

private:
    void displayMainMenu();
    void handleUserSelection(int selection);
    void showHomeStatus() const; // Option 1

    SystemMode currentMode;
    SystemState currentState;
};
