#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Assignment_Runner = Parser_String_Runner<&lloberon::Parser::parse_assignment_or_procedure_call>;
using Procedure_Call_Runner = Assignment_Runner;

TEST(Assignment_Tests, empty) {
    Assignment_Runner("", true);
}

TEST(Assignment_Tests, simple) {
    Assignment_Runner("a := 3");
}

TEST(Assignment_Tests, incomplete) {
    Assignment_Runner("a :=", true);
}

TEST(Procedure_Call_Tests, simple) {
    Procedure_Call_Runner("f()");
    Procedure_Call_Runner("f(a, 3)");
}

TEST(Procedure_Call_Tests, incomplete) {
    Procedure_Call_Runner("f(a,", true);
    Procedure_Call_Runner("f(a", true);
    Procedure_Call_Runner("f(", true);
}

TEST(Procedure_Call_Tests, cast) {
    Procedure_Call_Runner("a (INTEGER)");
}

#pragma clang diagnostic pop