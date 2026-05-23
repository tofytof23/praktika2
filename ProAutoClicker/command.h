#pragma once
#ifndef COMMAND_H_
#define COMMAND_H_

// Абстрактный базовый класс для всех действий (Паттерн Команда)
class Command {
public:
	virtual ~Command() = default;

	// Чисто виртуальный метод выполнения действия
	virtual void Execute() = 0;
};

// Команда для обеспечения временной задержки между действиями
class DelayCommand : public Command {
public:
	explicit DelayCommand(int milliseconds) : milliseconds_(milliseconds) {}
	~DelayCommand() override = default;

	void Execute() override;

private:
	int milliseconds_;
};

#endif  // COMMAND_H_