#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

class Instruction {
	public:
		Instruction(const string inputstr);
		void print() const;
	private:
		string action_name;
		float xCoord;
		float yCoord;
};

int main() {
	string line;
	string filepath = "/Users/sam/Documents/Metropolia/Y3/Y3Q1/Project/mDraw/gcode01.txt";
	
	ifstream myfile(filepath);
	
	// look for newline rather than using getline		
	while(getline (myfile, line)) {
		if (strncmp(&line[0], "M1", 1) == 0) {
			cout << "Move up/down" << endl;
		} else if (strncmp(&line[0], "G1", 2) == 0) {
			cout << "Go somewhere" << endl;
			Instruction newInstr(line);
			newInstr.print();
		} else {
			cout << "Other" << endl;
		}
		//cout << line << endl;
		line.erase(); // Necessary?
	}

	
	return 0;
}

Instruction::Instruction(const string inputstr) {
	size_t xpos = inputstr.find("X") + 1;
	size_t ypos = inputstr.find("Y") + 1;
	char* end_ptr;
	
	string xstr = inputstr.substr(xpos);
	string ystr = inputstr.substr(ypos);
	
	xCoord = strtof(xstr.c_str(), &end_ptr);
	yCoord = strtof(ystr.c_str(), &end_ptr);
}

void Instruction::print() const {
	cout << "X: " << xCoord << endl << "Y: " << yCoord << endl;
}