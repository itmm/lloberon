#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Repeat_Statement_Runner = Parser_String_Runner<&lloberon::Parser::parse_repeat_statement>;

TEST(Repeat_Statement_Tests, empty) {
    Repeat_Statement_Runner("", true);
}

TEST(Repeat_Statement_Tests, simple) {
    Repeat_Statement_Runner("REPEAT a := a + 1 UNTIL a > 10");
}

#pragma clang diagnostic pop