#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "ident-def-tests.h"
#include "parser-tests.h"

using Ident_Def_Runner = Parser_Value_Runner<sema::Ident_Def, &Parser::parse_ident_def>;

TEST(IDent_Def_Tests, empty) {
    sema::Ident_Def ident_def { "x", true };
    Ident_Def_Runner { "", ident_def, true };
    expect_empty_ident_def(ident_def);
}

TEST(Ident_Def_Tests, simple_ident) {
    sema::Ident_Def ident_def { "x", true };
    Ident_Def_Runner { "abc", ident_def };
    expect_ident_def(ident_def, "abc", false);
}

TEST(Ident_Def_Tests, exported_ident) {
    sema::Ident_Def ident_def { "x", false };
    Ident_Def_Runner { "abc*", ident_def };
    expect_ident_def(ident_def, "abc", true);
}

TEST(Ident_Def_Tests, empty_isnt_ident) {
    sema::Ident_Def ident_def { "x", true };
    Ident_Def_Runner { "", ident_def, true };
    expect_empty_ident_def(ident_def);
}

TEST(Ident_Def_Tests, number_isnt_ident) {
    sema::Ident_Def ident_def { "x", true };
    Ident_Def_Runner { "123", ident_def, true, true };
    expect_empty_ident_def(ident_def);
}

TEST(Ident_Def_Tests, star_isnt_ident) {
    sema::Ident_Def ident_def { "x", true };
    Ident_Def_Runner("*", ident_def, true, true);
    expect_empty_ident_def(ident_def);
}

#pragma clang diagnostic pop