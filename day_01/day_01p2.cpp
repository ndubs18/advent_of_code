#include <iostream>
#include <fstream>

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

		substring = s.substr(1, len-1);
		int num = std::stoi(substring);

		int remainder = num % 100;

		if (num >= 100) {
			int rotations = num / 100;
			zeroCount += rotations;
		}

		if (dir == 'L') {
			const int ogDialPos = dialPos;
			dialPos = dialPos - remainder;
			if (dialPos < 0) {
				if (ogDialPos != 0) ++zeroCount;
				dialPos = dialPos + 100;
			}
			if (dialPos == 0) {
				++zeroCount;
			}
		}
		else {
			dialPos = dialPos + remainder;
			// Only way to land on zero is by wrapping,
			// so we don't neet to check for zeros :) 
			if (dialPos > 99) {
				++zeroCount;
				dialPos = dialPos - 100;
			} 
		}
	}	
	std::cout << zeroCount << std::endl;

	return 0;
}
