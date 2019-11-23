#pragma once
#include <memory>
#include <optional>
#include "HRMLDOM.h"

using namespace std;

class AttributeParser {
	shared_ptr<HRMLDOM> dom;
public:
	AttributeParser(shared_ptr<HRMLDOM> aDom);
	optional<string> parse(string selector);
};

