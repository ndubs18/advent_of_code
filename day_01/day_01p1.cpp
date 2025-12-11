#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
	std::ifstream stream = std::ifstream("rotations.txt", std::ifstream::in);

	if (!stream.is_open()) {
		std::cout << "Couldn't open file\n";
	}

	if (stream.peek() == EOF) {
		std::cout << "The file is empty\n";	
	}

	int dialPos = 50;
	char chunk[10] {};
	int zeroCount {0};

	while (stream.getline(chunk, 10)) {
		int len = strlen(chunk);
		char dir = chunk[0];

		std::string s = std::string(chunk);

		std::string substring {};

		if (len < 3) {
			substring = s.substr(1, 1);
		}
		else {
			substring = s.substr(len-2, 2);
		}

		int num = std::stoi(substring);

		if (dir == 'L') {
			if (num > dialPos) {
				dialPos = 99 - (num - dialPos) + 1;	
			} else {
				dialPos -= num;
			}
		}
		else if (dir == 'R') {
			if (num > (99 - dialPos)) {
				dialPos = 0 + num - (99 - dialPos) - 1;
			} else {
				dialPos += num;
			}
		}

		if (dialPos == 0) {
			zeroCount += 1;
		}
	}

	std::cout << zeroCount << std::endl;

	return 0;
}

