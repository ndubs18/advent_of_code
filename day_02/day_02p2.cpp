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

	for (const auto& r : ranges) {
		for (size_t num = r.start; num <= r.end; ++num) {
			size_t numDigits {0};

			unsigned long long number {num};
			while (number > 0) {
				++numDigits;
				number /= 10;
			}

			for (size_t seqSize = 1; seqSize < numDigits; ++seqSize) {
				if (numDigits % seqSize != 0) continue;
				
				size_t magnitude {1};
				for(size_t i = 0; i < seqSize; ++i) {
					magnitude *= 10;
				}
					
				size_t sequence {num % magnitude};
				size_t n {num};
				bool invalid {true};

				while (n > 0) {
					if (n % magnitude != sequence) {
						invalid = false;
						break;
					}
					n /= magnitude;
				}
				if (invalid) {
					sum += num;
					break;
				}
			}

		}

	}

	std::cout << sum << std::endl;

	stream.close();	
	return 0;
}
