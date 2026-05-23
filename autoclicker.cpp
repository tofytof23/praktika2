#include "autoclicker.h"
#include <windows.h>
#include <iostream>
#include <thread>  
#include <chrono>  
#include "mouse_commands.h"

void Autoclicker::StartRecording() {
    history_.clear();
    last_x_ = -1;
    last_y_ = -1;
    is_recording_ = true;
    last_time_point_ = std::chrono::steady_clock::now();
    std::cout << "[INFO] Recording STARTED. Move your mouse and click...\n";
}

void Autoclicker::StopRecording() {
    is_recording_ = false;
    std::cout << "[INFO] Recording STOPPED. Recorded command blocks: " << history_.size() << "\n";
}

void Autoclicker::RecordCurrentState() {
    if (!is_recording_) return;

    POINT current_pos;
    // Статический флаг, чтобы знать, зажали мы ЛКМ или только что кликнули
    static bool was_clicked_before = false;

    if (GetCursorPos(&current_pos)) {
        bool click_detected = (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
        bool mouse_moved = (current_pos.x != last_x_ || current_pos.y != last_y_);

        // Клик произошел ТОЛЬКО если сейчас кнопка нажата, а в прошлый шаг была отпущена
        bool fresh_click = click_detected && !was_clicked_before;
        was_clicked_before = click_detected; // запоминаем состояние для следующего шага

        if (mouse_moved || fresh_click) {
            auto current_time = std::chrono::steady_clock::now();
            int elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                current_time - last_time_point_).count();

            // Если прошло хотя бы немного времени, пишем задержку
            if (elapsed_ms > 0) {
                history_.push_back(std::make_unique<DelayCommand>(elapsed_ms));
            }

            // Записываем движение
            if (mouse_moved) {
                history_.push_back(std::make_unique<MouseMoveCommand>(current_pos.x, current_pos.y));
                last_x_ = current_pos.x;
                last_y_ = current_pos.y;
            }

            // Записываем точный одиночный клик без всяких sleep_for!
            if (fresh_click) {
                history_.push_back(std::make_unique<MouseClickCommand>());
            }

            last_time_point_ = std::chrono::steady_clock::now();
        }
    }
}

void Autoclicker::Playback(int cycles) {
    if (history_.empty()) {
        std::cout << "[WARN] Nothing to play! History is empty.\n";
        return;
    }

    std::cout << "[INFO] Starting playback for " << cycles << " cycles...\n";
    std::cout << "[INFO] PRESS 'ESC' AT ANY TIME TO FORCE STOP PLAYBACK!\n";

    for (int i = 0; i < cycles; ++i) {
        std::cout << "[INFO] Cycle " << (i + 1) << " in progress...\n";

        for (const auto& command : history_) {
            // Аварийная проверка: если нажата клавиша ESC (код VK_ESCAPE)
            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                std::cout << "\n[EMERGENCY] Playback FORCE STOPPED by user!\n";
                return; // Мгновенно выходим из метода, прерывая все циклы
            }

            command->Execute(); // Выполнение текущей команды (движение, клик или пауза)
        }
    }
    std::cout << "[INFO] Playback finished completely.\n";
}