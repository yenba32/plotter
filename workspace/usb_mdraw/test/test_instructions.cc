#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <stdlib.h>
#include <iomanip>

#include "instruction.h"

using namespace std;

#define RUN_TEST(func) do { std::cout << #func; func(); std::cout << "\tOK" << endl; } while(false);

void testParseG1() {
	Instruction i;

	assert(Instruction::parse("G1 X-12.00 Y12.00 A0", &i) == 0);

	assert(i.type == InstructionType::MOVE);
	assert(i.param1 == -1200);
	assert(i.param2 == 1200);
}

void testParseG28() {
	Instruction i;

	assert(Instruction::parse("G28", &i) == 0);
	assert(i.type == InstructionType::MOVE_TO_ORIGIN);
}

void testParseM10() {
	Instruction i;
	assert(Instruction::parse("M10", &i) == 0);
	assert(i.type == InstructionType::REPORT_STATUS);
}

void testParseM1() {
	Instruction i;
	assert(Instruction::parse("M1 160", &i) == 0);
	assert(i.type == InstructionType::SET_PEN);
	assert(i.param1 == 160);
}

void testParseM2() {
	Instruction i;

	assert(Instruction::parse("M2 U160 D90", &i) == 0);
	assert(i.type == InstructionType::SET_PEN_RANGE);
	assert(i.param1 == 160);
	assert(i.param2 == 90);
}

void testParseM4() {
	// TODO: what if param1 > 255 or param1 < 0?
	Instruction i;
	assert(Instruction::parse("M4 255", &i) == 0);
	assert(i.type == InstructionType::SET_LASER);
	assert(i.param1 == 255);
}

void testParseM5() {
	Instruction i;
	assert(Instruction::parse("M5 A0 B1 H300 W123 S80", &i) == 0);
	assert(i.type == InstructionType::SAVE_DIR_AREA_SPEED);
	assert(i.param1 == 0);
	assert(i.param2 == 1);
	assert(i.param3 == 300);
	assert(i.param4 == 123);
	assert(i.param5 == 80);
}

void assertParseWholeFile(string filepath) {
	// parse the whole file into memory structs then convert that list into
	// string again then compare with the original string

	string line;

	ifstream myfile(filepath);
	std::stringstream buffer;

	while(getline(myfile, line)) {
		Instruction newInstr;

		Instruction::parse(line, &newInstr);
		buffer << setprecision(2) << fixed;

		switch (newInstr.type) {
			case InstructionType::MOVE:
			buffer << "G1 " << "X" << newInstr.param1 / 100.0 << " " << "Y" << newInstr.param2 / 100.0 << " A0";
			break;

			case InstructionType::MOVE_TO_ORIGIN:
			buffer << "G28";
			break;

			case InstructionType::REPORT_STATUS:
			buffer << "M10";
			break;

			case InstructionType::SET_LASER:
			buffer << "M4 " << newInstr.param1;
			break;

			case InstructionType::SET_PEN:
			buffer << "M1 " << newInstr.param1;
			break;
		}

		buffer << '\r';

		assert(line.compare(buffer.str()) == 0);

		line.erase();
		buffer.str("");
		buffer.clear();
	}
}

void testParseWholeFile() {
	assertParseWholeFile("gcode01.txt");
	assertParseWholeFile("gcode02.txt");
}


int main() {
	RUN_TEST(testParseG1);
	RUN_TEST(testParseG28);
	RUN_TEST(testParseM1);
	RUN_TEST(testParseM2);
	RUN_TEST(testParseM10);
	RUN_TEST(testParseM4);
	RUN_TEST(testParseWholeFile);

	return 0;
}
