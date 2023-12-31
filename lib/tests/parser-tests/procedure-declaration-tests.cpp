#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Procedure_Declaration_Runner = Parser_String_Runner<&lloberon::Parser::parse_procedure_declaration>;

TEST(Procedure_Declaration_Tests, empty) {
    Procedure_Declaration_Runner("", true);
}

TEST(Procedure_Declaration_Tests, simple) {
    Procedure_Declaration_Runner(
        "PROCEDURE Add1(x: INTEGER): INTEGER; RETURN x + 1 END Add1"
    );
}

TEST(Procedure_Declaration_Tests, incomplete) {
    Procedure_Declaration_Runner("PROCEDURE RETURN", true, true);
    Procedure_Declaration_Runner("PROCEDURE Answer(): INTEGER; RETURN", true);
}

#pragma clang diagnostic pop