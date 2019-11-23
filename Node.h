#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>

using namespace std;

class Node {
public:
	Node(const string input);
	// Given a real world project these would probably be private fields
	// with a public getter, if necessary.
	string name;
	map<string, string> attributes;
	vector<shared_ptr<Node>> children;
};

