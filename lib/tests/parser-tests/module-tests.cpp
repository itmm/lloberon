#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Module_Runner = Parser_String_Runner<&lloberon::Parser::parse_module>;

TEST(Module_Tests, empty) {
    Module_Runner("", true);
}

TEST(Module_Tests, simple) {
    Module_Runner("MODULE A; END A.");
}

TEST(Module_Tests, with_imports) {
    Module_Runner("MODULE A; IMPORT x := y; END A.");
}

TEST(Module_Tests, with_declarations) {
    Module_Runner("MODULE A; CONST B = 3; END A.");
}

TEST(Module_Tests, with_statements) {
    Module_Runner("MODULE A; BEGIN EXIT(10) END A.");
}

TEST(Module_Tests, with_multiple) {
    Module_Runner("MODULE A; IMPORT x; CONST B = 3; BEGIN EXIT(B) END A.");
    Module_Runner("MODULE A; IMPORT x; CONST B = 3; END A.");
    Module_Runner("MODULE A; IMPORT x; BEGIN EXIT(10) END A.");
    Module_Runner("MODULE A; CONST B = 3; BEGIN EXIT(B) END A.");
}

TEST(Module_Tests, names_dont_match) {
    Module_Runner("MODULE A; END B.", true, true);
}

TEST(Module_Tests, no_semicolon) {
    Module_Runner("MODULE A END A.", true, true);
}

TEST(Module_Tests, no_period) {
    Module_Runner("MODULE A; END A", true);
}

TEST(Module_Tests, no_names) {
    Module_Runner("MODULE END.", true, true);
    Module_Runner("MODULE A END.", true, true);
    Module_Runner("MODULE END A.", true, true);
}

TEST(Module_Tests, wrong_order) {
    Module_Runner("MODULE A; CONST B = 3; IMPORT x; END A.", true, true);
}

#pragma clang diagnostic pop