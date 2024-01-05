#include "parser-tests.h"

using Length_Runner = Parser_String_Runner<&Parser::parse_length>;

TEST(Length_Tests, empty) {
    Length_Runner test1 { "", true };
}

TEST(Length_Tests, simple) {
    Length_Runner test2 { "3" };
}