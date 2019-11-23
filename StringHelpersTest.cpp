#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "StringHelpers.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StringHelpersTest {
	TEST_CLASS(LeftTrim) {
		void testLtrim(string input, string expected) {
			Assert::AreEqual(ltrim(input), expected);
		}

	public:
		TEST_METHOD(NoWhitespace) {
			testLtrim("test", "test");
		}
		TEST_METHOD(CanTrimASpace) {
			testLtrim(" test", "test");
		}
		TEST_METHOD(CanTrimANewLine) {
			testLtrim("\ntest", "test");
		}
		TEST_METHOD(CanTrimAnyCharacter) {
			Assert::AreEqual(ltrim("*test", "*"), (string)"test");
		}
	};
	TEST_CLASS(RightTrim) {
		void testRtrim(string input, string expected) {
			Assert::AreEqual(rtrim(input), expected);
		}

	public:
		TEST_METHOD(NoWhitespace) {
			testRtrim("test", "test");
		}
		TEST_METHOD(CanTrimASpace) {
			testRtrim("test ", "test");
		}
		TEST_METHOD(CanTrimANewLine) {
			testRtrim("test\n", "test");
		}
		TEST_METHOD(CanTrimAnyCharacter) {
			Assert::AreEqual(rtrim("test*", "*"), (string)"test");
		}
	};
	TEST_CLASS(Trim) {
		void testTrim(string input, string expected) {
			Assert::AreEqual(trim(input), expected);
		}

	public:
		TEST_METHOD(NoWhitespace) {
			testTrim("test", "test");
		}
		TEST_METHOD(CanTrimASpace) {
			testTrim(" test ", "test");
		}
		TEST_METHOD(CanTrimANewLine) {
			testTrim("\ntest\n", "test");
		}
		TEST_METHOD(CanTrimAnyCharacter) {
			Assert::AreEqual(trim("*test*", "*"), (string)"test");
		}
	};
	TEST_CLASS(Split) {
	public:
		TEST_METHOD(StandardDelimiter) {
			vector<string> tokens = split((string)"one|two", '|');
			Assert::AreEqual(tokens.size(), (size_t)2);
			Assert::AreEqual(tokens.at(0), (string)"one");
			Assert::AreEqual(tokens.at(1), (string)"two");
		}
		TEST_METHOD(HandlesNoMatchingDelimiter) {
			vector<string> tokens = split((string)"one|two", ';');
			Assert::AreEqual(tokens.size(), (size_t)1);
			Assert::AreEqual(tokens.at(0), (string)"one|two");
		}
	};
}


