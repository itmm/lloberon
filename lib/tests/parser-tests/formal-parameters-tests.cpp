#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Formal_Parameters_Runner = Parser_String_Runner<&lloberon::Parser::parse_formal_parameters>;

TEST(Formal_Parameters_Tests, empty) {
    Formal_Parameters_Runner("", true);
}

TEST(Formal_Parameters_Tests, simple) {
    Formal_Parameters_Runner("()");
    Formal_Parameters_Runner("(VAR a: BYTE)");
}

TEST(Formal_Parameters_Tests, with_return) {
    Formal_Parameters_Runner("(): SYSTEM.Byte");
}

TEST(Formal_Parameters_Tests, incomplete) {
    Formal_Parameters_Runner("(", true);
    Formal_Parameters_Runner("():", true);
}

#pragma clang diagnostic pop