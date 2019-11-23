#include "pch.h"
#include "StringHelpers.h"
#include <sstream>

const string WHITESPACE = " \n";

string ltrim(const string input) {
	return ltrim(input, WHITESPACE);
}

string ltrim(const string input, const string trim) {
	size_t start = input.find_first_not_of(trim);
	return input.substr(start, -1);
}

string rtrim(const string input) {
	return rtrim(input, WHITESPACE);
}

string rtrim(const string input, const string toRemove) {
	size_t end = input.find_last_not_of(toRemove);
	return input.substr(0, end + 1);
}

string trim(const string input) {
	return trim(input, WHITESPACE);
}

string trim(const string input, const string toRemove) {
	return rtrim(ltrim(input, toRemove), toRemove);
}

vector<string> split(const string input, const char delimiter) {
	string token;
	vector<string> tokens = vector<string>();
	stringstream inputStream(input);
	while (getline(inputStream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}
