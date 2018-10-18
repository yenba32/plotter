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
	CALIBRATE,
	SAVE_DIR_AREA_SPEED,
	UNKNOWN
};

class Instruction {
public:
	static int parse(const std::string inputstr, Instruction *out);
	Instruction(InstructionType type = InstructionType::UNKNOWN,
			int param1 = 0,
			int param2 = 0,
			int param3 = 0,
			int param4 = 0,
			int param5 = 0)
	: type(type), param1(param1), param2(param2), param3(param3), param4(param4), param5(param5)
	{};

	InstructionType type;
	int param1;
	int param2;
	int param3;
	int param4;
	int param5;
};
