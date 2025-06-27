#include "Windows.h"
#include "FileLogger.h"
#include "ConsoleLogger.h"
#include "CompositeLogger.h"
#include "KeyEvent.h"
#include "KeyboardListener.h"

int main()
{
    std::cout << "Hello World!\n";

    auto logger = std::make_shared<CompositeLogger>();
    logger->AddLogger(std::make_shared<ConsoleLogger>());
    logger->AddLogger(std::make_shared<FileLogger>("keyboard_log.txt"));

    CKeyboardListener listener;
    listener.SetLogger(logger);
    listener.Init();

    listener.RegisterHandler(VK_F1, [](const KeyEvent& evt) {
        if (evt.state == KeyState::Down)
            std::cout << "[F1] Yardým tuþuna basildi!" << std::endl;
        });

    listener.RegisterHandler('A', [](const KeyEvent& evt) {
        if (evt.state == KeyState::Down && evt.ctrl)
            std::cout << "CTRL + A kombinasyonu!" << std::endl;
        });

    listener.RegisterHandler('S', [=](const KeyEvent& evt) {
        if (evt.state == KeyState::Down && evt.alt)
            std::cout << "ALT + S kombinasyonu!" << std::endl;
        });

    listener.RegisterHandler('Q', [=](const KeyEvent& evt) {
        if (evt.state == KeyState::Down && evt.ctrl && evt.shift && !evt.alt)
            std::cout << "CTRL + SHIFT + Q kombinasyonu!" << std::endl;
        });

    listener.RegisterHandler(VK_OEM_PERIOD, [=](const KeyEvent& evt) {
        if (evt.state == KeyState::Down && evt.shift && !evt.ctrl && !evt.alt)
            std::cout << "SHIFT + > kombinasyonu!" << std::endl;
        });

    listener.RegisterHandler('Q', [=](const KeyEvent& evt) {
        if (evt.state == KeyState::Down && evt.ctrl && evt.alt)
            std::cout << "AltGr + Q kombinasyonu!" << std::endl;
        });

    listener.RegisterHandler(VK_RMENU, [=](const KeyEvent& evt) {
        if (evt.state == KeyState::Down)
            std::cout << "Right Alt (AltGr) basildi!" << std::endl;
        });

    listener.RegisterHandler(VK_SPACE, [](const KeyEvent& evt) {
        if (evt.state == KeyState::Down)
            system("cls");
        }); 

    listener.Start();

    // Ana döngü - ESC ile çýkýlýr
    while (listener.IsRunning()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    listener.Stop();

    // Tuþ geçmiþini yazdýr
    auto& history = listener.GetKeyHistory();
    std::cout << "\nTus Gecmisi:\n";

    for (const auto& pair : history) {
        int vk = pair.first;
        const auto& hist = pair.second;
        std::cout << "VK: " << std::setw(3) << vk
            << " - Pressed: " << hist.pressCount
            << " - Last State: " << (hist.lastState == KeyState::Down ? "Down" :
                                     hist.lastState == KeyState::Hold ? "Hold" : "Up")
            << std::endl;
    }

    return 0;
}
