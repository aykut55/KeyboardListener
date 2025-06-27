#include "CKeyboardListener.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"
#include "CompositeLogger.h"
#include "KeyEvent.h"
#include <iostream>
#include <iomanip>

int main() {
    auto logger = std::make_shared<CompositeLogger>();
    logger->AddLogger(std::make_shared<ConsoleLogger>());
    logger->AddLogger(std::make_shared<FileLogger>("keyboard_log.txt"));

    CKeyboardListener listener;
    listener.SetLogger(logger);
    listener.Init();

    listener.RegisterHandler(VK_F1, [](const KeyEvent& evt) {
        if (evt.state == KeyState::Down)
            std::cout << "[F1] Yardım tuşuna basıldı!" << std::endl;
    });

    listener.RegisterHandler('A', [](const KeyEvent& evt) {
        if (evt.state == KeyState::Down && evt.ctrl)
            std::cout << "CTRL + A kombinasyonu!" << std::endl;
    });

    listener.Start();

    // Ana döngü - ESC ile çıkılır
    while (listener.IsRunning()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    listener.Stop();

    // Tuş geçmişini yazdır
    auto& history = listener.GetKeyHistory();
    std::cout << "\nTuş Geçmişi:\n";
    for (const auto& [vk, hist] : history) {
        std::cout << "VK: " << std::setw(3) << vk
                  << " - Pressed: " << hist.pressCount
                  << " - Last State: " << (hist.lastState == KeyState::Down ? "Down" :
                                            hist.lastState == KeyState::Hold ? "Hold" : "Up")
                  << std::endl;
    }

    return 0;
}