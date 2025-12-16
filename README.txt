================================================================================
                    MY SWEET HOME SYSTEM (MSH) v2.0
                        User and Developer Guide
================================================================================

PROJECT OVERVIEW
================================================================================

My Sweet Home System is a comprehensive home automation control system that manages
smart devices and system modes/states. It provides a unified interface for users to
control lights, cameras, TVs, detectors, and music systems across different modes
and performance states.

ARCHITECTURE
================================================================================

The system is organized into the following core modules:

1. CORE SYSTEM (MSHSystem)
   - Main controller and menu interface
   - Coordinates all subsystems
   - Manages user interactions
   - File: MSHSystem.h, MSHSystem.cpp

2. DEVICE SUBSYSTEM (modules/devices/)
   - Device base class with common functionality
   - Specific device implementations: Light, Camera, TV, SmokeGasDetector, MusicSystem
   - DeviceManager: centralized device registry and control
   - DeviceStatus: enumeration for device states
   - Files: Device.h, Light.h, Camera.h, TV.h, SmokeGasDetector.h, MusicSystem.h, DeviceManager.h

3. MODE SUBSYSTEM (ModeSubsystem_Bashir/)
   - Defines system operating modes: Normal, Evening, Party, Cinema
   - Each mode automatically configures devices appropriately
   - Strategy pattern implementation
   - Files: Mode.h, NormalMode.h, EveningMode.h, PartyMode.h, CinemaMode.h

4. STATE SUBSYSTEM (state/)
   - System performance states: Normal, Sleep, HighPerformance
   - Controls power and camera/light performance
   - State pattern implementation
   - Files: State.h, NormalState.h, SleepState.h, HighPerformanceState.h

DESIGN PATTERNS USED
================================================================================

1. Strategy Pattern
   - Modes implement the Mode interface
   - Different behaviors for different modes
   - Each mode defines how devices should be configured

2. State Pattern
   - States implement the State interface
   - Controls system performance characteristics
   - Determines power-saving and performance levels

3. Factory Pattern
   - DeviceManager creates and manages devices
   - Simplifies device instantiation
   - Centralized device lifecycle management

SYSTEM MODES
================================================================================

NORMAL MODE (Default)
  - Intended for everyday use
  - Lights: OFF
  - Cameras: OFF
  - Detectors: ON
  - TVs: OFF
  - Music: OFF

EVENING MODE
  - Suitable for nighttime and when leaving home
  - Lights: OFF
  - Cameras: ON
  - Detectors: ON
  - TVs: OFF
  - Music: OFF

PARTY MODE
  - For social gatherings and entertainment
  - Lights: ON
  - Cameras: ON
  - Detectors: ON
  - TVs: OFF
  - Music: ON

CINEMA MODE
  - For movie watching or entertainment
  - Lights: OFF (to not interfere with screen)
  - Cameras: ON
  - Detectors: ON
  - TVs: ON
  - Music: OFF

PERFORMANCE STATES
================================================================================

NORMAL STATE
  - Balanced performance and power consumption
  - Camera Performance: NORMAL
  - Light Mode: NORMAL
  - Power Saving: OFF

SLEEP STATE
  - Minimal power consumption, essential services only
  - Non-essential devices turned OFF
  - Camera Performance: SLEEP (low/monitoring only)
  - Light Mode: OFF
  - Power Saving: ON

HIGH PERFORMANCE STATE
  - Maximum performance for all devices
  - All systems run at peak capability
  - Camera Performance: HIGH
  - Light Mode: MAX
  - Power Saving: OFF

SUPPORTED DEVICES
================================================================================

1. LIGHT
   - Properties: ID, Name, Brightness (0-100)
   - Can be turned ON/OFF
   - Brightness is configurable
   - Example: Living Room Light, Bedroom Light

2. CAMERA
   - Properties: ID, Name, FPS (frames per second), Night Vision capability
   - Can be turned ON/OFF
   - Supports variable frame rates (typically 15-60 FPS)
   - Night vision capability for low-light monitoring
   - Example: Front Door Camera, Backyard Camera

3. TV
   - Properties: ID, Name, Brand, Volume (0-100)
   - Can be turned ON/OFF
   - Volume is configurable
   - Example: Living Room TV, Bedroom TV

4. SMOKE & GAS DETECTOR
   - Properties: ID, Name, Sensitivity (1-10)
   - Can be turned ON/OFF
   - Sensitivity level adjustable
   - Essential for safety
   - Example: Kitchen Detector, Basement Detector

5. MUSIC SYSTEM
   - Properties: ID, Name, Volume (0-100)
   - Can be turned ON/OFF
   - Volume is configurable
   - Example: Living Room Speaker, Outdoor Speaker

USAGE GUIDE
================================================================================

STARTING THE APPLICATION
  $ ./build.sh          # Build the project
  $ ./a.out             # Run the application (or use CMake)

MAIN MENU OPTIONS
  1. Get Home Status
     - View current mode and state
     - List all connected devices with their status
     - Display camera performance and light mode

  2. Add Device
     - Select device type
     - Enter device name and properties
     - Device is automatically registered in the system

  3. Remove Device
     - View all devices
     - Select device by ID to remove
     - Device is unregistered from the system

  4. Control Device
     - Select a device
     - Turn ON or OFF
     - Immediate state change

  5. Change Mode
     - Select new operating mode
     - All devices are automatically reconfigured
     - Mode-specific device settings applied instantly

  6. Change State
     - Select performance state
     - System adjusts power and performance settings
     - Display brightness and camera performance adjusted

  7. Manual
     - Display help information
     - Shows description of all menu options

  8. About
     - View system information
     - List supported devices and features

  0. Exit
     - Gracefully shutdown the application

DEVICE MANAGEMENT
================================================================================

ADDING DEVICES
  1. Select "Add Device" from main menu
  2. Choose device type:
     - Light (with brightness parameter)
     - Camera (with FPS and night vision option)
     - TV (with brand selection)
     - Smoke & Gas Detector (with sensitivity level)
     - Music System (with volume control)
  3. Enter device name (e.g., "Living Room Light")
  4. Configure device-specific parameters
  5. Device appears in inventory immediately

REMOVING DEVICES
  1. Select "Remove Device" from main menu
  2. View list of all connected devices
  3. Enter device ID to remove
  4. Device is removed and no longer controllable

CONTROLLING DEVICES
  1. Select "Control Device" from main menu
  2. Select device from list by ID
  3. Choose ON or OFF action
  4. Device state changes immediately

AUTOMATIC MODE-BASED CONTROL
  When a mode is changed, devices are automatically configured:
  - Lights turn ON/OFF per mode specifications
  - Cameras activate/deactivate automatically
  - TVs and music systems adjust based on mode
  - Detectors remain active for safety in all modes

TECHNICAL DETAILS
================================================================================

ENUM DEFINITIONS

SystemMode:
  - Normal
  - Evening
  - Party
  - Cinema

SystemState:
  - Normal
  - Sleep
  - HighPerformance

DeviceStatus:
  - ACTIVE    (device functioning normally)
  - INACTIVE  (device powered off but functional)
  - FAILED    (device malfunction)

HEADER FILES CONVENTIONS
  - All headers use #pragma once
  - Forward declarations where appropriate
  - Const-correctness maintained throughout
  - Virtual destructors in base classes

MEMORY MANAGEMENT
  - Uses std::shared_ptr for devices
  - Automatic cleanup on removal
  - No manual memory management required

DEVICE PROPERTIES STORED
  - int id: unique identifier
  - std::string name: user-friendly name
  - bool isOn: power state
  - DeviceStatus status: operational status
  - Device-specific properties (brightness, volume, fps, etc.)

BUILDING THE PROJECT
================================================================================

REQUIREMENTS
  - C++11 or later
  - CMake 3.0 or later
  - Standard C++ library

COMPILATION
  $ cmake .              # Generate build files
  $ cmake --build .      # Compile the project
  or
  $ ./build.sh          # Run provided build script

EXAMPLE SESSION
================================================================================

Welcome to My Sweet Home System!

=== My Sweet Home System ===
Current Mode: Normal | State: Normal
Devices: 0

1. Get Home Status
2. Add Device
3. Remove Device
4. Control Device
5. Change Mode
6. Change State
7. Manual
8. About
0. Exit
Select: 2

=== ADD DEVICE ===
Device Types:
1. Light
2. Camera
3. TV
4. Smoke & Gas Detector
5. Music System
Select type: 1
Enter device name: Living Room Light
Enter brightness (0-100) [default 50]: 75
Light added successfully!

[After adding several devices and changing mode to Party...]

=== CHANGE MODE ===
Available Modes:
1. Normal
2. Evening
3. Party
4. Cinema
Select mode: 3
Mode changed to: Party
Devices updated accordingly.

=== HOME STATUS ===
Current Mode: Party
Current State: Normal
Camera Performance: NORMAL
Light Mode: NORMAL
Power Saving: OFF

Devices (5 total):
  ID 1: Light [Living Room Light] - Brightness: 75 [ON]
  ID 2: Camera [Front Door] - FPS: 30, Night Vision: OFF [ON]
  ID 3: Smoke & Gas Detector [Kitchen] - Sensitivity: 5 [ON]
  ID 4: Music System [Living Room] - Volume: 15 [ON]
  ID 5: TV [Living Room] - Brand: Samsung, Volume: 10 [OFF]

FUTURE ENHANCEMENTS
================================================================================

Potential features for future versions:

1. SCHEDULING
   - Automatic mode transitions at specific times
   - Cron-like job scheduling

2. AUTOMATION RULES
   - "If detector triggers, activate all cameras"
   - Scene-based automation

3. PERSISTENCE
   - Save/load device configurations
   - Device state logging

4. NETWORK INTEGRATION
   - Remote control via network
   - IoT device integration

5. ADVANCED MONITORING
   - Device health monitoring
   - Usage statistics and logging

6. ENERGY MANAGEMENT
   - Power consumption tracking
   - Energy optimization recommendations

7. SCENE CREATION
   - Custom scenes beyond predefined modes
   - User-defined device configurations

TROUBLESHOOTING
================================================================================

ISSUE: Device not appearing in inventory
SOLUTION: Verify device was successfully added. Check that device type selection was valid.

ISSUE: Mode change didn't affect devices
SOLUTION: Ensure all devices are ACTIVE (not FAILED). Try changing mode again.

ISSUE: Device not responding to ON/OFF command
SOLUTION: Check if device status is FAILED. Remove and re-add the device.

ISSUE: Application crashes when adding device
SOLUTION: Verify input values are within valid ranges (brightness 0-100, FPS > 0, etc.)

SUPPORT & CREDITS
================================================================================

My Sweet Home System v2.0
Created by: Team MSH
Contributors:
  - Main System: Mahmoud Jalloh
  - Mode Subsystem: Bashir
  - Device Management: Team
  - State Management: Team

For issues or questions, please refer to individual module documentation
or source code comments.

================================================================================
                            END OF DOCUMENTATION
================================================================================
