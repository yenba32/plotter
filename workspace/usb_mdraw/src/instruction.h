#pragma once

#include <string>

enum class InstructionType {
	MOVE,
	MOVE_TO_ORIGIN,
	REPORT_STATUS,
	SET_PEN,
	SET_LASER,
	LIMIT_QUERY,
	UNKNOWN
};

class Instruction {
public:
	static Instruction parse(const std::string inputstr);
	Instruction(InstructionType type = InstructionType::UNKNOWN, int param1 = 0, int param2 = 0): type(type), param1(param1), param2(param2) {};

	const InstructionType type;
	const int param1;
	const int param2;
};
