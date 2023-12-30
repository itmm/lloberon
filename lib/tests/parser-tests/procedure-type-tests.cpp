#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Procedure_Type_Runner = Parser_String_Runner<&lloberon::Parser::parse_procedure_type>;

TEST(Procedure_Type_Tests, empty) {
    Procedure_Type_Runner("", true);
}

TEST(Procedure_Type_Tests, simple) {
    Procedure_Type_Runner("PROCEDURE (a: INTEGER): BYTE");
}

#pragma clang diagnostic pop