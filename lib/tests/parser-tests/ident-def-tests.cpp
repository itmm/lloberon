#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Ident_Def_Runner = Parser_String_Runner<&lloberon::Parser::parse_ident_def>;

TEST(Ident_Def_Tests, simple_ident) {
    Ident_Def_Runner("abc");
}

TEST(Ident_Def_Tests, exported_ident) {
    Ident_Def_Runner("abc*");
}

TEST(Ident_Def_Tests, empty_isnt_ident) {
    Ident_Def_Runner("", true);
}

TEST(Ident_Def_Tests, number_isnt_ident) {
    Ident_Def_Runner("123", true, true);
}

TEST(Ident_Def_Tests, star_isnt_ident) {
    Ident_Def_Runner("*", true, true);
}

#pragma clang diagnostic pop