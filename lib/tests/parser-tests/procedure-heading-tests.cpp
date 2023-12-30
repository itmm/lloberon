#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Procedure_Heading_Runner = Parser_String_Runner<&lloberon::Parser::parse_procedure_heading>;

TEST(Procedure_Heading_Tests, empty) {
    Procedure_Heading_Runner("", true);
}

TEST(Procedure_Heading_Tests, simple) {
    Procedure_Heading_Runner("PROCEDURE f(x: INTEGER): BOOLEAN");
}

TEST(Procedure_Heading_Tests, incomplete) {
    Procedure_Heading_Runner("PROCEDURE f", true);
    Procedure_Heading_Runner("PROCEDURE (): BYTE", true, true);
}

#pragma clang diagnostic pop