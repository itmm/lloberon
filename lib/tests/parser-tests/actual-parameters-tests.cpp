#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Actual_Parameters_Runner = Parser_String_Runner<&lloberon::Parser::parse_actual_parameters>;

TEST(Actual_Parameters_Tests, empty) {
    Actual_Parameters_Runner("", true);
    Actual_Parameters_Runner("()");
}

TEST(Actual_Parameters_Tests, simple) {
    Actual_Parameters_Runner("(3, 4)");
}

TEST(Actual_Paramaters_Tests, incomplete) {
    Actual_Parameters_Runner("a", true, true);
    Actual_Parameters_Runner("(a", true);
    Actual_Parameters_Runner("(", true);
}

#pragma clang diagnostic pop