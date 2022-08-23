#pragma once
#include <random>

class Random {
public:
	static void Init() {
		s_Randomizer.seed(std::random_device()());
	}

	static float Dist() {
		return (float)s_Distribution(s_Randomizer) / (float)std::numeric_limits<uint32_t>::max(); //returns random number between 0 and 1
	}
private:
	static std::mt19937 s_Randomizer;
	static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
};