#include "Windows.h"
#include "FileLogger.h"
#include "ConsoleLogger.h"
#include "CompositeLogger.h"
#include "KeyEvent.h"
#include "KeyboardListener.h"
#include "Aircraft.h"

int main1()
{
    std::cout << "Hello World!\n";

    auto logger = std::make_shared<CompositeLogger>();
    logger->AddLogger(std::make_shared<ConsoleLogger>());
    logger->AddLogger(std::make_shared<FileLogger>("keyboard_log.txt"));

    CKeyboardListener listener;
    listener.SetSilentMode(true);
    listener.SetLogger(logger);
    listener.Init();

    listener.RegisterHandler(VK_F1, [](const KeyEvent& evt) {
        if (evt.state == KeyState::Down)
            std::cout << "[F1] Yardým tusuna basildi!" << std::endl;
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
        if (evt.state == KeyState::Down)
            std::cout << "Q tusuna basildi!" << std::endl;
        });

    listener.RegisterHandler('Q', [=](const KeyEvent& evt) {
        if (evt.state == KeyState::Down && evt.ctrl && evt.shift && !evt.alt)
            std::cout << "CTRL + SHIFT + Q kombinasyonu!" << std::endl;
        });

    listener.RegisterHandler('Q', [=](const KeyEvent& evt) {
        if (evt.state == KeyState::Down && evt.ctrl)
            std::cout << "CTRL + Q kombinasyonu!" << std::endl;
        });

    listener.RegisterHandler('Q', [=](const KeyEvent& evt) {
        if (evt.state == KeyState::Down && evt.shift)
            std::cout << "SHIFT + Q kombinasyonu!" << std::endl;
        });

    listener.RegisterHandler('Q', [=](const KeyEvent& evt) {
        if (evt.state == KeyState::Down && evt.alt)
            std::cout << "ALT + Q kombinasyonu!" << std::endl;
        });

    listener.RegisterHandler('Q', [=](const KeyEvent& evt) {
        if (evt.state == KeyState::Down && evt.ctrl && evt.alt)
            std::cout << "AltGr + Q kombinasyonu!" << std::endl;
        });

    listener.RegisterHandler(VK_OEM_PERIOD, [=](const KeyEvent& evt) {
        if (evt.state == KeyState::Down && evt.shift && !evt.ctrl && !evt.alt)
            std::cout << "SHIFT + > kombinasyonu!" << std::endl;
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

int main2() 
{
    auto logger = std::make_shared<ConsoleLogger>();

    auto listener = std::make_shared<CKeyboardListener>();
    listener->SetSilentMode(true);
    listener->SetLogger(logger);

    listener->Init();

    listener->Start();

    Aircraft aircraft;

    auto lastPrint = std::chrono::steady_clock::now();

    while (listener->IsRunning()) 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        aircraft.IncIterCount();

        auto keys = listener->GetKeyHistoryCopy();

        // Farklý kullanim ornegi olsun diye koyuldu
        if (keys.count(VK_DELETE) && keys.at(VK_DELETE).isPressed)
            system("cls");

        if (keys[VK_ESCAPE].isPressed) {
            logger->Log("ESC detected. Exiting...");
            break;
        }

        // ======== Yön Tuþlarý ile Kontrol ========

        if (keys[VK_LEFT].isPressed)
            aircraft.RollLeft();

        if (keys[VK_RIGHT].isPressed) 
            aircraft.RollRight();

        if (keys[VK_UP].isPressed)
            aircraft.PitchDown();

        if (keys[VK_DOWN].isPressed)
            aircraft.PitchUp();

        if (keys['A'].isPressed)      
            aircraft.YawLeft();

        if (keys['D'].isPressed)      
            aircraft.YawRight();

        // Page Up
        if (keys[VK_PRIOR].isPressed)   
            aircraft.ThrottleUp();
        
        // Page Down
        if (keys[VK_NEXT].isPressed) 
            aircraft.ThrottleDown();

        if (keys[VK_SPACE].isPressed)
            aircraft.NeutralizeAll();


        // ======== NUMPAD Tuþlarý ile Kontrol ========

        if (keys.count(VK_NUMPAD4) && keys.at(VK_NUMPAD4).wasPressed)
            aircraft.StartRollLeft();

        if (keys.count(VK_NUMPAD6) && keys.at(VK_NUMPAD6).wasPressed)
            aircraft.StartRollRight();

        if (keys.count(VK_NUMPAD8) && keys.at(VK_NUMPAD8).wasPressed)
            aircraft.StartPitchDown();

        if (keys.count(VK_NUMPAD2) && keys.at(VK_NUMPAD2).wasPressed)
            aircraft.StartPitchUp();

        if (keys.count(VK_NUMPAD7) && keys.at(VK_NUMPAD7).wasPressed)
            aircraft.StartYawLeft();

        if (keys.count(VK_NUMPAD9) && keys.at(VK_NUMPAD9).wasPressed)
            aircraft.StartYawRight();

        if (keys.count(VK_ADD) && keys.at(VK_ADD).wasPressed)
            aircraft.StartThrottleUp();

        if (keys.count(VK_SUBTRACT) && keys.at(VK_SUBTRACT).wasPressed)
            aircraft.StartThrottleDown();

        if (keys.count(VK_NUMPAD5) && keys.at(VK_NUMPAD5).wasPressed) {
            aircraft.StopRolling();
            aircraft.StopPitching();
            aircraft.StopYawing();
            aircraft.StopThrottle();
        }

        aircraft.Update();

        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastPrint).count() > 20) {
            lastPrint = now;
        }

        aircraft.PrintStatus();
    }

    listener->Stop();

    return 0;
}

int main()
{
    std::cout << "Hello World!\n";

    main2();

    return 0;
}