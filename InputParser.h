#pragma once
#include <string>
#include <vector>

using namespace std;

class InputParser {
public:
	InputParser(const string input);
	// Given a real world project these would probably be private fields
	// with a public getter, if necessary.
	string hrml;
	vector<string> selectors;
};

