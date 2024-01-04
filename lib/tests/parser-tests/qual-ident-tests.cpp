#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Qual_Ident_Runner = Parser_String_Runner<&lloberon::Parser::parse_qual_ident>;

TEST(Qual_Ident_Tests, empty) {
    Qual_Ident_Runner("", true);
}

TEST(Qual_Ident_Tests, simple) {
    Qual_Ident_Runner("a");
    Qual_Ident_Runner("a.b");
}

TEST(Qual_Ident_Tests, incomplete) {
    Qual_Ident_Runner("a.", true);
    Qual_Ident_Runner(".", true, true);
}

#pragma clang diagnostic pop