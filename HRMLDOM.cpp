#include "pch.h"
#include "HRMLDOM.h"
#include "StringHelpers.h"

HRMLDOM::HRMLDOM(const string hrml) {
	parseNodes(hrml, nullptr);
}

/*
  Similar to the browser's `document.querySelector` this method will only return the first
  matching node regardless if multiple are found. If this project were expanded i'd like to see
  an equivalent method to `document.querySelectorAll`.
*/
shared_ptr<Node> HRMLDOM::query(const string selector) {
	auto nodeTokens = split(selector, '.');
	return findNode(nodeTokens, roots);
}

/*
  Breadth-first search to traverse the DOM. Obviously not the most efficient approach
  but i'm not concerned with that given this small project.
*/
shared_ptr<Node> HRMLDOM::findNode(vector<string> nodeTokens, vector<shared_ptr<Node>> nodes) {
	auto matchedFirstToken = vector<shared_ptr<Node>>();
	for (auto node : nodes) {
		if (node->name == nodeTokens[0]) {
			matchedFirstToken.push_back(node);
		}
	}
	if (!matchedFirstToken.empty()) {
		if (nodeTokens.size() == 1) {
			return matchedFirstToken[0];
		}
		nodeTokens.erase(nodeTokens.begin());
		auto children = vector<shared_ptr<Node>>();
		for (auto matched : matchedFirstToken) {
			children.insert(children.end(), begin(matched->children), end(matched->children));
		}
		return findNode(nodeTokens, children);
	}
	return nullptr;
}

size_t HRMLDOM::parseNodes(const string hrml, shared_ptr<Node> current) {
	size_t tagStartsAt = string::npos;
	bool inClosingTag = false;
	size_t iCopy = 0;
	for (size_t i = 0; i < hrml.size(); i++) {
		iCopy = i;
		const char c = hrml[i];
		if (c == '<') {
			tagStartsAt = i;
			continue;
		}
		if (c == '/' && tagStartsAt == (i - 1)) {
			inClosingTag = true;
			continue;
		}
		if (c == '>' && inClosingTag) {
			break;
		}
		if (c == '>' && tagStartsAt != string::npos) {
			shared_ptr<Node> tmp(new Node(hrml.substr(tagStartsAt, i + 1)));
			if (!current) {
				roots.push_back(tmp);
			} else {
				current->children.push_back(tmp);
			}
			i += parseNodes(hrml.substr(i + 1), tmp);
			continue;
		}
	}
	return iCopy + 1;
}
