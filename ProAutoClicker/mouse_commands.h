#pragma once
#ifndef MOUSE_COMMANDS_H_
#define MOUSE_COMMANDS_H_

#include "command.h"

// Команда перемещения курсора мыши
class MouseMoveCommand : public Command {
public:
	MouseMoveCommand(int x, int y) : x_(x), y_(y) {}
	~MouseMoveCommand() override = default;

	void Execute() override;

private:
	int x_;
	int y_;
};

// Команда клика левой кнопкой мыши (ЛКМ)
class MouseClickCommand : public Command {
public:
	MouseClickCommand() = default;
	~MouseClickCommand() override = default;

	void Execute() override;
};

#endif  // MOUSE_COMMANDS_H_