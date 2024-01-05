#include "parser-tests.h"

using Parse_Runner = Parser_String_Runner<&Parser::parse>;

TEST(Parse_Tests, empty) {
    Parse_Runner test1 { "", true };
}

TEST(Parse_Tests, simple) {
    Parse_Runner test2 { "MODULE A; END A." };
}

TEST(Parse_Tests, invalid) {
    Parse_Runner test3 { "MODULE A END", true, true };
}