#include "pch.h"
#include "InputParser.h"
#include "StringHelpers.h"
#include <iostream>
#include <sstream>
#include <iterator>

using namespace std;

InputParser::InputParser(const string input) {
	stringstream inputStream(input);

	vector<string> lines = split(input, '\n');
	vector<string> countTokens = split(lines[0], ' ');
	int countLineCount = 1;
	int hrmlLineCount = stoi(countTokens.at(0));
	int selectorsLineCount = stoi(countTokens.at(1));

	/* Pull HRML from lines */
	int hrmlOffset = countLineCount + hrmlLineCount;
	vector<string> hrmlSubsetLines(lines.begin() + countLineCount, lines.begin() + hrmlOffset);
	stringstream joinStream;
	copy(hrmlSubsetLines.begin(), hrmlSubsetLines.end(), ostream_iterator<string>(joinStream, "\n"));
	hrml = trim(joinStream.str());

	/* Pull selectors from lines */
	selectors = vector<string>(lines.begin() + hrmlOffset, lines.begin() + (hrmlOffset + selectorsLineCount));
}
