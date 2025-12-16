#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Device.h"
#include "Light.h"
#include "Camera.h"
#include "TV.h"
#include "SmokeGasDetector.h"
#include "MusicSystem.h"

class DeviceManager {
private:
    std::vector<std::shared_ptr<Device>> devices;
    int nextDeviceId;

public:
    DeviceManager() : nextDeviceId(1) {}

    // Add a device to the system
    std::shared_ptr<Device> addDevice(std::shared_ptr<Device> device) {
        devices.push_back(device);
        return device;
    }

    // Remove a device by ID
    bool removeDevice(int id) {
        for (auto it = devices.begin(); it != devices.end(); ++it) {
            if ((*it)->getId() == id) {
                devices.erase(it);
                return true;
            }
        }
        return false;
    }

    // Find device by ID
    std::shared_ptr<Device> findDevice(int id) {
        for (auto& device : devices) {
            if (device->getId() == id) {
                return device;
            }
        }
        return nullptr;
    }

    // Get all devices
    const std::vector<std::shared_ptr<Device>>& getAllDevices() const {
        return devices;
    }

    // Get device count
    size_t getDeviceCount() const {
        return devices.size();
    }

    // Control functions for different device types
    void setAllLights(bool on) {
        for (auto& device : devices) {
            Light* light = dynamic_cast<Light*>(device.get());
            if (light) {
                if (on) light->turnOn();
                else light->turnOff();
            }
        }
    }

    void setAllCameras(bool on) {
        for (auto& device : devices) {
            Camera* camera = dynamic_cast<Camera*>(device.get());
            if (camera) {
                if (on) camera->turnOn();
                else camera->turnOff();
            }
        }
    }

    void setAllTVs(bool on) {
        for (auto& device : devices) {
            TV* tv = dynamic_cast<TV*>(device.get());
            if (tv) {
                if (on) tv->turnOn();
                else tv->turnOff();
            }
        }
    }

    void setAllMusicSystems(bool on) {
        for (auto& device : devices) {
            MusicSystem* music = dynamic_cast<MusicSystem*>(device.get());
            if (music) {
                if (on) music->turnOn();
                else music->turnOff();
            }
        }
    }

    void setAllSmokeGasDetectors(bool on) {
        for (auto& device : devices) {
            SmokeGasDetector* detector = dynamic_cast<SmokeGasDetector*>(device.get());
            if (detector) {
                if (on) detector->turnOn();
                else detector->turnOff();
            }
        }
    }

    // Create helper functions for device creation
    std::shared_ptr<Light> createLight(const std::string& name, int brightness = 50) {
        auto light = std::make_shared<Light>(nextDeviceId++, name, brightness);
        addDevice(light);
        return light;
    }

    std::shared_ptr<Camera> createCamera(const std::string& name, int fps = 30, bool nightVision = false) {
        auto camera = std::make_shared<Camera>(nextDeviceId++, name, fps, nightVision);
        addDevice(camera);
        return camera;
    }

    std::shared_ptr<TV> createTV(const std::string& name, const std::string& brand = "Generic", int volume = 10) {
        auto tv = std::make_shared<TV>(nextDeviceId++, name, brand, volume);
        addDevice(tv);
        return tv;
    }

    std::shared_ptr<SmokeGasDetector> createSmokeGasDetector(const std::string& name, int sensitivity = 5) {
        auto detector = std::make_shared<SmokeGasDetector>(nextDeviceId++, name, sensitivity);
        addDevice(detector);
        return detector;
    }

    std::shared_ptr<MusicSystem> createMusicSystem(const std::string& name, int volume = 15) {
        auto music = std::make_shared<MusicSystem>(nextDeviceId++, name, volume);
        addDevice(music);
        return music;
    }
};
