#include "mouse_commands.h"
#include <windows.h>

void MouseMoveCommand::Execute() {
	double screen_width = GetSystemMetrics(SM_CXSCREEN) - 1;
	double screen_height = GetSystemMetrics(SM_CYSCREEN) - 1;

	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	// Нормализация координат под требования Windows API (0 - 65535)
	input.mi.dx = static_cast<LONG>(x_ * (65535.0 / screen_width));
	input.mi.dy = static_cast<LONG>(y_ * (65535.0 / screen_height));
	input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;

	SendInput(1, &input, sizeof(INPUT));
}

void MouseClickCommand::Execute() {
	INPUT inputs[2] = { 0 };

	// Нажатие ЛКМ
	inputs[0].type = INPUT_MOUSE;
	inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	// Отпускание ЛКМ
	inputs[1].type = INPUT_MOUSE;
	inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

	SendInput(2, inputs, sizeof(INPUT));
}
