#include "MSHSystem.h"
#include <iostream>
#ifdef _WIN32
#include <conio.h> // For non-blocking input on Windows
#else
// POSIX implementation for non-Windows: termios + select
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>

static struct termios orig_termios;
static bool termios_initialized = false;

static void init_termios() {
    if (termios_initialized) return;
    if (tcgetattr(STDIN_FILENO, &orig_termios) == 0) {
        struct termios newt = orig_termios;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        termios_initialized = true;
    }
}

static void reset_termios() {
    if (!termios_initialized) return;
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
    termios_initialized = false;
}

static inline int _kbhit() {
    init_termios();
    struct timeval tv = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

static inline int _getch() {
    init_termios();
    int c = getchar();
    return c;
}
#endif
#include <thread>

// Global variable for MSHSystem access
MSHSystem* globalMSHSystem = nullptr;

// Function to check for alarm input
void checkForAlarmInput(MSHSystem& system) {
    // This function runs continuously to check for user input during alarms
    while (true) {
        if (system.isAlarmActive() && _kbhit()) { // Check if key pressed
            _getch(); // Read the key
            system.handleAlarmAcknowledgment(); // Acknowledge alarm
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Small delay
    }
}

int main() {
    MSHSystem msh;
    // Support non-interactive self-test mode
    extern char **environ;
    // Check argv via main signature change: use standard argc/argv by overloading isn't possible here,
    // so read from /proc for simplicity when needed. Instead, detect env var AUTO_TEST=1 or command line via getenv.
    // Prefer CLI flag: read `argc/argv` by inspecting `/proc/self/cmdline`.
    bool autoTest = false;
    FILE* f = fopen("/proc/self/cmdline", "r");
    if (f) {
        std::string cmd;
        int c;
        while ((c = fgetc(f)) != EOF) {
            if (c == '\0') cmd.push_back(' ');
            else cmd.push_back((char)c);
        }
        fclose(f);
        if (cmd.find("--auto-test") != std::string::npos) autoTest = true;
    }
    globalMSHSystem = &msh; // Set global pointer / تعيين المؤشر العام
    
    std::cout << "========================================" << std::endl;
    std::cout << "     MY SWEET HOME (MSH) SYSTEM        " << std::endl;
    std::cout << "     Alarm System by Ahmed Essalem     " << std::endl;
    std::cout << "========================================" << std::endl;
    
    // Start thread for alarm input checking
    std::thread inputThread(checkForAlarmInput, std::ref(msh));
    inputThread.detach(); // Detach to run independently

    // Ensure terminal restored on exit (POSIX)
#ifndef _WIN32
    atexit(reset_termios);
#endif
    
    // Start main system
    if (autoTest) {
        msh.runAutoTest();
        return 0;
    }

    msh.run(); // Using run() as shown in the photo
    
    return 0;
}
