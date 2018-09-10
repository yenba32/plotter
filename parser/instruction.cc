#include "instruction.h"

using namespace std;

Instruction parseG1(const string line);

Instruction Instruction::parse(const string line) {
	static const string G28("G28");
	static const string M10("M10");
	static const string G1("G1");
	static const string M1("M1");
	static const string M4("M4");

	if (line.compare(0, G28.size(), G28) == 0) {
		return Instruction(InstructionType::MOVE_TO_ORIGIN);
	}

	if (line.compare(0, G1.size(), G1) == 0) {
		return parseG1(line.substr(G1.size()));
	}

	if (line.compare(0, M10.size(), M10) == 0) {
		return Instruction(InstructionType::REPORT_STATUS);
	}

	if (line.compare(0, M1.size(), M1) == 0) {
		string penParam = line.substr(2);
		return Instruction(InstructionType::SET_PEN, stoi(penParam));
	}

	if (line.compare(0, M4.size(), M4) == 0) {
		string laserParam = line.substr(2);
		return Instruction(InstructionType::SET_LASER, stoi(laserParam));
	}

	throw "Unknown command";
}

Instruction parseG1(const string line) {
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

	return Instruction(InstructionType::MOVE, xPos, yPos);
}