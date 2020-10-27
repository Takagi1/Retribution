#pragma once

#include <random>

/// <summary>
/// Return random number between two values
/// </summary>
class RandomNumber {
public:
	static int GetRandom(const int min, const int max) {
		int diff = max;
		if (min < 0) { diff += -min; }
		else { diff += min; }
		
		return (rand() % diff) + min;
	}
};