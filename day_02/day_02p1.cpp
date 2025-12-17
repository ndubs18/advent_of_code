#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct range {
	size_t start;
	size_t end;
};

int main (int argc, char* argv[]) {
	std::string path {"id_ranges.txt"};
	
	if (argc > 1) {
		path = argv[1];
	}
	
	std::ifstream stream {path, std::ios::in};
	if (!stream) {
		return 1;
	}

	if (!stream.peek()) {
		std::cout << "There's nothing to read in the file\n" << std::endl;
		return 0;
	}

	std::vector<range> ranges {};
	ranges.reserve(50);

	std::string rangesStr {};

	std::getline(stream, rangesStr);

	size_t start{};
	size_t commaIdx{};
	size_t dashIdx{};

	while (commaIdx != rangesStr.npos) {
		dashIdx = rangesStr.find('-', start);
		commaIdx = rangesStr.find(',', start);
		
		range cur{};
		
		cur.start = std::stoull(rangesStr.substr(start, dashIdx));
		cur.end = std::stoull(rangesStr.substr(dashIdx + 1, commaIdx - dashIdx + 1));

		ranges.push_back(cur);
		start = commaIdx + 1;
	}

	size_t sum {0};

	for(const auto& r : ranges) {
				
		for (size_t num = r.start; num <= r.end; ++num) {
			int numDigits {0};
			size_t tempNum = num;
			while (tempNum != 0) {
				tempNum /= 10;
				++numDigits;
			}

			if (numDigits % 2 != 0) continue;

			size_t halfNum1 {num};
			size_t modBy {1};	 

			for (int i = 0; i < numDigits / 2; ++i) {
				halfNum1 /= 10;
				modBy *= 10;
			}
			
			size_t halfNum2 {num % modBy};

			if (halfNum1 == halfNum2) {
				sum += num;	
			}
			
		}

	}

	std::cout << sum << std::endl;

	stream.close();	
	return 0;
}
