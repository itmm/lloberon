#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Formal_Parameter_Section_Runner = Parser_String_Runner<&lloberon::Parser::parse_formal_parameter_section>;

TEST(Formal_Parameter_Section_Tests, empty) {
    Formal_Parameter_Section_Runner("", true);
}

TEST(Formal_Parameter_Section_Tests, simple) {
    Formal_Parameter_Section_Runner("a: ARRAY OF INTEGER");
}

TEST(Formal_Parameter_Section_Tests, multiple) {
    Formal_Parameter_Section_Runner("a, b: INTEGER");
}

TEST(Formal_Parameter_Section_Tests, var_parameter) {
    Formal_Parameter_Section_Runner("VAR a: INTEGER");
}

TEST(Formal_Parameter_Section_Tests, incomplete) {
    Formal_Parameter_Section_Runner("VAR", true);
    Formal_Parameter_Section_Runner("a,", true);
    Formal_Parameter_Section_Runner("a INTEGER", true, true);
}

#pragma clang diagnostic pop