#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "Node.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NodeTest {
	TEST_CLASS(NodeTest) {
	public:
		TEST_METHOD(NodeName) {
			unique_ptr<Node> node(new Node((string)"<test>"));
			Assert::AreEqual(node->name, (string)"test");
			Assert::AreEqual(node->attributes.size(), (size_t)0);
		}
		TEST_METHOD(NodeNameWithNumber) {
			unique_ptr<Node> node(new Node((string)"<test9>"));
			Assert::AreEqual(node->name, (string)"test9");
			Assert::AreEqual(node->attributes.size(), (size_t)0);
		}
		TEST_METHOD(LeadingWhitespaceName) {
			unique_ptr<Node> node(new Node((string)"<   test>"));
			Assert::AreEqual(node->name, (string)"test");
		}
		TEST_METHOD(TrailingWhitespaceName) {
			unique_ptr<Node> node(new Node((string)"<test   >"));
			Assert::AreEqual(node->name, (string)"test");
		}
		TEST_METHOD(CanParseAttribute) {
			unique_ptr<Node> node(new Node((string)"<test attr=\"blargh\">"));
			Assert::AreEqual(node->attributes.size(), (size_t)1);
			Assert::AreEqual(node->attributes.at("attr"), (string)"blargh");
		}
		TEST_METHOD(CanParseAttributeWithNumber) {
			unique_ptr<Node> node(new Node((string)"<test attr1=\"blargh\">"));
			Assert::AreEqual(node->attributes.size(), (size_t)1);
			Assert::AreEqual(node->attributes.at("attr1"), (string)"blargh");
		}
		TEST_METHOD(CanParseAttributeWithWhitespace) {
			unique_ptr<Node> node(new Node((string)"<test attr  =  \" blargh \"  >"));
			Assert::AreEqual(node->attributes.size(), (size_t)1);
			Assert::AreEqual(node->attributes.at("attr"), (string)" blargh ");
		}
	};
}
