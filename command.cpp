#include "command.h"
#include <windows.h>
#include <thread>
#include <chrono>

void DelayCommand::Execute() {
    if (milliseconds_ > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_));
    }
}