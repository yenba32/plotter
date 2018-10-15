#include "instruction.h"

#include "stdio.h"

using namespace std;

int parseM2(const string line, Instruction *out);
int parseG1(const string line, Instruction *out);

int Instruction::parse(const string line, Instruction* out) {
	static const string G28("G28");
	static const string G1("G1");

	static const string M10("M10");
	static const string M11("M11");
	static const string M1("M1");
	static const string M2("M2");
	static const string M4("M4")
	static const string M28("M28");

	if (line.compare(0, M28.size(), M28) == 0) {
		*out = Instruction(InstructionType::CALIBRATE);
		return 0;
	}

	if (line.compare(0, G28.size(), G28) == 0) {
		*out = Instruction(InstructionType::MOVE_TO_ORIGIN);
		return 0;
	}

	if (line.compare(0, M11.size(), M11) == 0) {
		*out = Instruction(InstructionType::LIMIT_QUERY);
		return 0;
	}

	if (line.compare(0, G1.size(), G1) == 0) {
		return parseG1(line, out);
	}

	if (line.compare(0, M10.size(), M10) == 0) {
		*out = Instruction(InstructionType::REPORT_STATUS);
		return 0;
	}

	if (line.compare(0, M2.size(), M2) == 0) {
		return parseM2(line, out);
	}

	if (line.compare(0, M1.size(), M1) == 0) {
		string penParam = line.substr(2);
		*out = Instruction(InstructionType::SET_PEN, stoi(penParam));
		return 0;
	}

	if (line.compare(0, M4.size(), M4) == 0) {
		string laserParam = line.substr(2);
		*out = Instruction(InstructionType::SET_LASER, stoi(laserParam));
		return 0;
	}

	return -1;
}

int parseM2(const string line, Instruction *out) {
	int up = 0;
	int down = 0;
	int result = sscanf(line.c_str(), "M2 U%d D%d", &up, &down);

	if (result != 2) return -1;

	*out = Instruction(InstructionType::SET_PEN_RANGE, up, down);
	return 0;
}


int parseG1(const string line, Instruction *out) {
	string currentParam;
	int phase = 0;
	int xPos = 0;
	int yPos = 0;

	// "G1 X-23.01 Y32.00 A0"
	// assuming X and Y params are given in that order:
	//
	// phase 0: skip chars until after X
	// phase 1: copy digits, skipping the dot (.) then parse to xPos
	// phase 2: skip chars until after Y
	// phase 3: copy digits, skipping the dot (.) then parse to yPos
	//
	// the A0 part is ignored

	for (const char& c : line) {
		if (phase == 0) {
			if (c == 'X') {
				phase = 1;
			}
			continue;
		}

		if (phase == 1 && c == ' ') {
			xPos = stoi(currentParam);

			phase = 2;
			currentParam.clear();
			continue;
		}

		if (phase == 2) {
			if (c == 'Y') {
				phase = 3;
			}
			continue;
		}

		if (phase == 3 && c == ' ') {
			yPos = stoi(currentParam);
			break;
		}

		if (c != '.') {
			currentParam += c;
		}
	}

	*out = Instruction(InstructionType::MOVE, xPos, yPos);
	return 0;
}
