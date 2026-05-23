#pragma once
#ifndef AUTOCLICKER_H_
#define AUTOCLICKER_H_

#include <vector>
#include <memory>
#include <chrono>
#include "command.h"

// Класс-Одиночка (Singleton), управляющий макросом
class Autoclicker {
public:
    // Потокобезопасный Синглтон Майерса
    static Autoclicker& GetInstance() {
        static Autoclicker instance;
        return instance;
    }

    // Запрещаем копирование и присваивание по правилам Google Style
    Autoclicker(const Autoclicker&) = delete;
    Autoclicker& operator=(const Autoclicker&) = delete;

    void StartRecording();
    void StopRecording();
    void RecordCurrentState();
    void Playback(int cycles);

    // Инлайн геттеры (в нижнем регистре по Google Style)
    bool is_recording() const { return is_recording_; }
    size_t GetActionsCount() const { return history_.size(); }

private:
    Autoclicker() : is_recording_(false), last_x_(-1), last_y_(-1) {}
    ~Autoclicker() = default;

    bool is_recording_;
    int last_x_;
    int last_y_;

    // Храним полиморфные умные указатели на базовый интерфейс команд
    std::vector<std::unique_ptr<Command>> history_;
    std::chrono::steady_clock::time_point last_time_point_;
};

#endif  // AUTOCLICKER_H_