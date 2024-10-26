#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "RegularFunctions.hpp"



bool isVowel(std::string guess) {
	if (guess.size() < 2) {
		transform(guess.begin(), guess.end(), guess.begin(), ::toupper);
		if (guess[0] == 'A' || guess[0] == 'E' || guess[0] == 'O' || guess[0] == 'I' || guess[0] == 'U') {
			return true;
		}
	}

	return false;
}


bool is_number(const std::string& s)
{
	return (s.size() == 1) && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}


void clearScreen() {
#ifdef _WIN32
	std::system("cls");
#else
	std::system("clear");
#endif
}