#include <iostream>

#include "Light.h"
#include "Camera.h"
#include "TV.h"
#include "SmokeGasDetector.h"
#include "MusicSystem.h"

int main() {
    Light l1(1, "Living Room Light");
    Camera c1(1, "Front Camera");
    TV tv1(1, "Main TV", "Samsung");
    SmokeGasDetector d1(1, "Kitchen Detector");
    MusicSystem m1(1, "Home Music");

    l1.turnOn();
    c1.turnOn();

    std::cout << l1.getInfo() << std::endl;
    std::cout << c1.getInfo() << std::endl;
    std::cout << tv1.getInfo() << std::endl;
    std::cout << d1.getInfo() << std::endl;
    std::cout << m1.getInfo() << std::endl;

    return 0;
}
