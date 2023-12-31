#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Procedure_Body_Runner = Parser_String_Runner<&lloberon::Parser::parse_procedure_body>;

TEST(Procedure_Body_Tests, empty) {
    Procedure_Body_Runner("", true);
}

TEST(Procedure_Body_Tests, simple) {
    Procedure_Body_Runner("END");
    Procedure_Body_Runner("RETURN 42 END");
    Procedure_Body_Runner("BEGIN RETURN 42 END");
    Procedure_Body_Runner("BEGIN a := 42; RETURN a END");
}

TEST(Procedure_Body_Tests, with_declaration) {
    Procedure_Body_Runner("VAR a: INTEGER; BEGIN a := 42 END");
    Procedure_Body_Runner("CONST a = 42; RETURN a END");
}

TEST(Procedure_Body_Tests, invalid) {
    Procedure_Body_Runner("RETURN END", true);
}

#pragma clang diagnostic pop