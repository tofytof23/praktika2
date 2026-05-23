#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "autoclicker.h"

int main() {
    // Получаем ссылку на единственный экземпляр кликера (Singleton)
    Autoclicker& clicker = Autoclicker::GetInstance();

    std::cout << "=========================================\n";
    std::cout << "   SOLID & Design Patterns Autoclicker   \n";
    std::cout << "=========================================\n";
    std::cout << " Hotkeys:\n";
    std::cout << "  F2 or Fn+F2  - Start / Stop Recording\n";
    std::cout << "  F3 or Fn+F3 - Play Recorded Actions\n";
    std::cout << "  F4 or Fn+F4 - Safe Exit Program\n";
    std::cout << "  ESC - EMERGENCY STOP (during playback)\n"; // <--- ДОБАВИЛИ СТРОЧКУ
    std::cout << "=========================================\n\n";

    while (true) {
        // Выход из программы
        if (GetAsyncKeyState(VK_F4) & 0x8000) {
            break;
        }

        // Переключение записи (Старт/Стоп)
        if (GetAsyncKeyState(VK_F2) & 0x8000) {
            if (clicker.is_recording()) {
                clicker.StopRecording();
            }
            else {
                clicker.StartRecording();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(350)); // Анти-дребезг
        }

        // Если активен режим записи — опрашиваем мышь
        if (clicker.is_recording()) {
            clicker.RecordCurrentState();
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Частота ~60 Гц
        }

        // Воспроизведение макроса
        if (GetAsyncKeyState(VK_F3) & 0x8000) {
            if (!clicker.is_recording()) {
                // Воспроизводим, например, 2 цикла. Можно сделать ввод через cin.
                clicker.Playback(1);
            }
            else {
                std::cout << "[WARN] Cannot playback while recording is active!\n";
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(350));
        }
    }

    std::cout << "[INFO] Application closed successfully.\n";
    return 0;
}