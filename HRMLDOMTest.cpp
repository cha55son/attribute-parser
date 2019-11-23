#include "pch.h"
#include <iostream>
#include "HRMLDOM.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HRMLDOMTest {
	TEST_CLASS(Parsing) {
	public:
		TEST_METHOD(CanParseASimpleNode) {
			unique_ptr<HRMLDOM> dom(new HRMLDOM("<test></test>"));
			Assert::AreEqual((size_t)1, dom->roots.size());
			Assert::AreEqual((string)"test", dom->roots.at(0)->name);
		}
		TEST_METHOD(CanParseMultipleRoots) {
			unique_ptr<HRMLDOM> dom(new HRMLDOM("<test1></test1><test2></test2>"));
			Assert::AreEqual((size_t)2, dom->roots.size());
			Assert::AreEqual((string)"test1", dom->roots.at(0)->name);
			Assert::AreEqual((string)"test2", dom->roots.at(1)->name);
		}
		TEST_METHOD(CanParseNestedNodes) {
			unique_ptr<HRMLDOM> dom(new HRMLDOM("<test><inner></inner></test>"));
			Assert::AreEqual((size_t)1, dom->roots.size());
			shared_ptr<Node> test = dom->roots.at(0);
			Assert::AreEqual((string)"test", test->name);
			Assert::AreEqual((size_t)1, test->children.size());
			Assert::AreEqual((string)"inner", test->children.at(0)->name);
		}
		TEST_METHOD(CanParseDeeplyNestedWithSiblings) {
			unique_ptr<HRMLDOM> dom(new HRMLDOM(
				"<test>\n"
					"<inner></inner>\n"
					"<inner2>\n"
						"<inner3></inner3>\n"
					"</inner2>\n"
				"</test>"
			));
			Assert::AreEqual((size_t)1, dom->roots.size());
			shared_ptr<Node> test = dom->roots.at(0);
			Assert::AreEqual((size_t)2, test->children.size());
			Assert::AreEqual((string)"inner", test->children.at(0)->name);
			shared_ptr<Node> inner2 = test->children.at(1);
			Assert::AreEqual((string)"inner2", inner2->name);
			Assert::AreEqual((size_t)1, inner2->children.size());
			Assert::AreEqual((string)"inner3", inner2->children.at(0)->name);
		}
	};
	TEST_CLASS(Querying) {
	public:
		TEST_METHOD(CanQueryForOneNode) {
			unique_ptr<HRMLDOM> dom(new HRMLDOM("<test></test>"));
			auto node = dom->query("test");
			Assert::IsNotNull(node.get());
			Assert::AreEqual(node.get()->name, (string)"test");
		}
		TEST_METHOD(CanQueryOneLevelDeep) {
			unique_ptr<HRMLDOM> dom(new HRMLDOM("<test><inner></inner></test>"));
			auto node = dom->query("test.inner");
			Assert::IsNotNull(node.get());
			Assert::AreEqual(node.get()->name, (string)"inner");
		}
		TEST_METHOD(CanQueryArbitraryLevelsDeep) {
			unique_ptr<HRMLDOM> dom(new HRMLDOM("<r><i1><i2><i3></i3></i2></i1></r>"));
			auto node = dom->query("r.i1.i2.i3");
			Assert::IsNotNull(node.get());
			Assert::AreEqual(node.get()->name, (string)"i3");
		}
	};
}
