#include "MSHSystem.h"
#include <iostream>
#include <conio.h> // For non-blocking input / للإدخال غير المتوقف
#include <thread>

// Global variable for MSHSystem access / متغير عام للوصول إلى MSHSystem
MSHSystem* globalMSHSystem = nullptr;

// Function to check for alarm input / دالة للتحقق من إدخال الإنذار
void checkForAlarmInput(MSHSystem& system) {
    // This function runs continuously to check for user input during alarms
    // هذه الدالة تعمل باستمرار للتحقق من إدخال المستخدم أثناء الإنذارات
    while (true) {
        if (system.isAlarmActive() && _kbhit()) { // Check if key pressed / التحقق من ضغط المفتاح
            _getch(); // Read the key / قراءة المفتاح
            system.handleAlarmAcknowledgment(); // Acknowledge alarm / إقرار الإنذار
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Small delay / تأخير بسيط
    }
}

int main() {
    MSHSystem msh;
    globalMSHSystem = &msh; // Set global pointer / تعيين المؤشر العام
    
    std::cout << "========================================" << std::endl;
    std::cout << "     MY SWEET HOME (MSH) SYSTEM        " << std::endl;
    std::cout << "        نظام منزلي الحلو (MSH)         " << std::endl;
    std::cout << "     Alarm System by Ahmed Essalem     " << std::endl;
    std::cout << "     نظام الإنذار من تطوير أحمد السلام     " << std::endl;
    std::cout << "========================================" << std::endl;
    
    // Start thread for alarm input checking / بدء خيط للتحقق من إدخال الإنذار
    std::thread inputThread(checkForAlarmInput, std::ref(msh));
    inputThread.detach(); // Detach to run independently / فصل للعمل بشكل مستقل
    
    // Start main system / بدء النظام الرئيسي
    msh.run(); // Using run() as shown in the photo
    
    return 0;
}
