#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "InputParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const string input =
"4 3\n"
"<tag1 value = \"HelloWorld\">\n"
	"<tag2 name = \"Name1\">\n"
	"</tag2>\n"
"</tag1>\n"
"tag1.tag2~name\n"
"tag1~name\n"
"tag1~value";

const string simpleInput =
"1 1\n"
"<tag1></tag1>\n"
"tag1~name";

namespace InputParserTest {
	TEST_CLASS(InputParserTest) {
	public:
		TEST_METHOD(CanParseTheHRML) {
			unique_ptr<InputParser> parser(new InputParser(simpleInput));
			Assert::AreEqual(parser->hrml, (string)"<tag1></tag1>");
		}
		TEST_METHOD(CanParseTheSelectors) {
			unique_ptr<InputParser> parser(new InputParser(simpleInput));
			Assert::AreEqual(parser->selectors.size(), (size_t)1);
			Assert::AreEqual(parser->selectors.at(0), (string)"tag1~name");
		}
	};
}

