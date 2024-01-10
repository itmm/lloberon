#include "parser-tests.h"

using Element_Runner = Parser_String_Runner<&Parser::parse_element>;

TEST(Element_Tests, empty) {
	Element_Runner test1 { "", true };
}

TEST(Element_Tests, simple) {
	Element_Runner test1 { "3" };
}

TEST(Element_Tests, range) {
	Element_Runner test1 { "3..6" };
}

TEST(Element_Tests, incomplete) {
	Element_Runner test1 { "3..", true };
}