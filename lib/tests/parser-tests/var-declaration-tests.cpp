#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Var_Declaration_Runner = Parser_String_Runner<&lloberon::Parser::parse_variable_declaration>;

TEST(Var_Declaration_Tests, empty) {
    Var_Declaration_Runner("", true);
}

TEST(Var_Declaration_Tests, simple) {
    Var_Declaration_Runner("a*: INTEGER");
}

TEST(Var_Declaration_Tests, incomplete) {
    Var_Declaration_Runner("a:", true);
    Var_Declaration_Runner("a", true);
}

TEST(Var_Declaration_Tests, invalid) {
    Var_Declaration_Runner("a INTEGER", true, true);
    Var_Declaration_Runner("a;", true, true);
}

#pragma clang diagnostic pop