#include "pch.h"
#include "AttributeParser.h"
#include "StringHelpers.h"

AttributeParser::AttributeParser(shared_ptr<HRMLDOM> aDom) {
	dom = aDom;
}

optional<string> AttributeParser::parse(string selector) {
	vector<string> selectorTokens = split(selector, '~');
	string nodeSelector = selectorTokens[0];
	string attributeSelector = selectorTokens[1];
	shared_ptr<Node> node = dom->query(nodeSelector);
	auto pair = node->attributes.find(attributeSelector);
	if (pair != node->attributes.end()) {
		return pair->second;
	}
	return nullopt;
}
