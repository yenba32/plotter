#pragma once

#include <string>

enum class InstructionType {
	MOVE,
	MOVE_TO_ORIGIN,
	REPORT_STATUS,
	SET_PEN,
	SET_LASER,
	LIMIT_QUERY,
	SET_PEN_RANGE,
	UNKNOWN
};

class Instruction {
public:
	static int parse(const std::string inputstr, Instruction *out);
	Instruction(InstructionType type = InstructionType::UNKNOWN, int param1 = 0, int param2 = 0): type(type), param1(param1), param2(param2) {};

	InstructionType type;
	int param1;
	int param2;
};
