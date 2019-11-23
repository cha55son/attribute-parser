#include "pch.h"
#include <iostream>
#include "Node.h"
#include <regex>
#include "StringHelpers.h"

Node::Node(const string input) {
	regex innerBracketRegex("<\\s*([a-zA-Z0-9]+)(\\s+[a-zA-Z0-9]+\\s*=\\s*\".*\")?\\s*>");
	smatch innerBracketMatch;
	regex_search(input, innerBracketMatch, innerBracketRegex);
	for (size_t i = 1; i < innerBracketMatch.size(); i++) {
		if (i == 1) {
			name = innerBracketMatch.str(i);
			continue;
		}
		ssub_match match = innerBracketMatch[i];
		if (!match.matched) { continue; }
		vector<string> attributeTokens = split(match.str(), '=');
		string attributeName = trim(attributeTokens.at(0));
		string attributeValue = trim(trim(attributeTokens.at(1)), "\"");
		attributes.insert(pair<string, string>(attributeName, attributeValue));
	}
}
