#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Const_Declaration_Runner = Parser_String_Runner<&lloberon::Parser::parse_const_declaration>;

TEST(Const_Declaration_Tests, empty) {
    Const_Declaration_Runner("", true);
}

TEST(Const_Decalaration_Tests, simple) {
    Const_Declaration_Runner("a* = 3 + 4");
}

TEST(Const_Declaration_Tests, incomplete) {
    Const_Declaration_Runner("a =", true);
    Const_Declaration_Runner("a", true);
}

#pragma clang diagnostic pop