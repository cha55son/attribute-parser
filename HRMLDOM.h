#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Node.h"

using namespace std;

class HRMLDOM {
	size_t parseNodes(const string hrml, shared_ptr<Node> current);
	shared_ptr<Node> findNode(vector<string> nodeTokens, vector<shared_ptr<Node>> nodes);
public:
	HRMLDOM(const string hrml);
	shared_ptr<Node> query(const string selector);
	// Given a real world project this would probably be a private field
	// with a public getter, if necessary.
	vector<shared_ptr<Node>> roots;
};
