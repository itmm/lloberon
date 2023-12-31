#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Parse_Runner = Parser_String_Runner<&lloberon::Parser::parse>;

TEST(Parse_Tests, empty) {
    Parse_Runner("", true);
}

TEST(Parse_Tests, simple) {
    Parse_Runner("MODULE A; END A.");
}

TEST(Parse_Tests, invalid) {
    Parse_Runner("MODULE A END", true, true);
}

#pragma clang diagnostic pop