#include "pch.h"
#include <iostream>
#include "CppUnitTest.h"
#include "InputParser.h"
#include "HRMLDOM.h"
#include "AttributeParser.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const string simple =
"1 1\n"
"<test name=\"hi\"></test>\n"
"test~name";

const string sample =
"4 3\n"
"<tag1 value = \"HelloWorld\">\n"
	"<tag2 name = \"Name1\">\n"
	"</tag2>\n"
"</tag1>\n"
"tag1.tag2~name\n"
"tag1~name\n"
"tag1~value";

/* Copied some HTML from the problem page */
const string advanced =
"22 3\n"
"<div class=\"community-content\">\n"
"	<div class=\"challenge-view theme-m\">\n"
"		<div class=\"challenge-page-header container\">\n"
"			<div class=\"ui-tabs-wrap\"></div>\n"
"		</div>\n"
"		<section class=\"challenge-interface challenge-problem\">\n"
"			<div class=\"challenge-body\">\n"
"				<div class=\"challenge-body-elements-problem challenge-container-element\">\n"
"					<div class=\"container challenge-page-wrap panes-container theme-m-content\">\n"
"						<div class=\"full-screen-split split-wrap left-pane\">\n"
"							<section class=\"problem-statement split\"></section>\n"
"							<section class=\"code-editor-section split\"></section>\n"
"						</div>\n"
"						<div class=\"right-pane\">\n"
"							<aside class=\"theme-m-content fullscreen-hide challenge-sidebar\"></aside>\n"
"						</div>\n"
"					</div>\n"
"				</div>\n"
"			</div>\n"
"		</section>\n"
"	</div>\n"
"</div>\n"
"div.div.section.div~class\n"
"div.div.section.div.div.div.div~class\n"
"div.div.section.div.div.div.div.section~class";

namespace AttributeParserTest {
	TEST_CLASS(Parsing) {
	public:
		TEST_METHOD(CanParseSimpleExample) {
			unique_ptr<InputParser> inputParser(new InputParser(simple));
			shared_ptr<HRMLDOM> dom(new HRMLDOM(inputParser->hrml));
			unique_ptr<AttributeParser> parser(new AttributeParser(dom));
			Assert::AreEqual((string)"hi", parser->parse(inputParser->selectors[0]).value());
		}
		TEST_METHOD(ReturnsEmptyObservableIfNoAttributeIsSpecified) {
			unique_ptr<InputParser> inputParser(new InputParser(simple));
			shared_ptr<HRMLDOM> dom(new HRMLDOM(inputParser->hrml));
			unique_ptr<AttributeParser> parser(new AttributeParser(dom));
			Assert::IsFalse(parser->parse("test~doesntExist").has_value());
		}
		TEST_METHOD(MatchProblemSampleOutput) {
			unique_ptr<InputParser> inputParser(new InputParser(sample));
			shared_ptr<HRMLDOM> dom(new HRMLDOM(inputParser->hrml));
			unique_ptr<AttributeParser> parser(new AttributeParser(dom));

			Assert::AreEqual((string)"Name1", parser->parse(inputParser->selectors[0]).value());
			Assert::IsFalse(parser->parse(inputParser->selectors[1]).has_value());
			Assert::AreEqual((string)"HelloWorld", parser->parse(inputParser->selectors[2]).value());
		}
		TEST_METHOD(AdvancedSampleHTML) {
			unique_ptr<InputParser> inputParser(new InputParser(advanced));
			shared_ptr<HRMLDOM> dom(new HRMLDOM(inputParser->hrml));
			unique_ptr<AttributeParser> parser(new AttributeParser(dom));

			Assert::AreEqual((string)"challenge-body", parser->parse(inputParser->selectors[0]).value());
			Assert::AreEqual((string)"full-screen-split split-wrap left-pane", parser->parse(inputParser->selectors[1]).value());
			Assert::AreEqual((string)"problem-statement split", parser->parse(inputParser->selectors[2]).value());
		}
	};
};
