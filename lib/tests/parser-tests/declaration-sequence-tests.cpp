#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Declaration_Sequence_Runner = Parser_String_Runner<&lloberon::Parser::parse_declaration_sequence>;

TEST(Declaration_Sequence_Tests, empty) {
    Declaration_Sequence_Runner("");
}

TEST(Declaration_Sequence_Tests, single) {
    Declaration_Sequence_Runner("CONST a = 3;");
    Declaration_Sequence_Runner("TYPE image = ARRAY 10 OF INTEGER;");
    Declaration_Sequence_Runner("VAR a: INTEGER;");
    Declaration_Sequence_Runner("PROCEDURE Nop(); BEGIN END Nop;");
}

TEST(Declaration_Sequence_Tests, multiple) {
    Declaration_Sequence_Runner("CONST a = 3; b = 4;");
    Declaration_Sequence_Runner("TYPE X = INTEGER; Y = BYTE;");
    Declaration_Sequence_Runner("VAR a: INTEGER; b: BYTE;");
    Declaration_Sequence_Runner(
        "PROCEDURE Nop(); BEGIN END Nop; PROCEDURE Nop2(); BEGIN END Nop2;"
    );
}

TEST(Declaration_Sequence_Tests, multiple_types) {
    Declaration_Sequence_Runner("CONST a = 3; TYPE x = BYTE;");
    Declaration_Sequence_Runner("TYPE x = BYTE; VAR a: BYTE;");
    Declaration_Sequence_Runner("VAR a: BYTE; PROCEDURE Nop(); BEGIN END Nop;");
    Declaration_Sequence_Runner("CONST a = 3; VAR a: BYTE;");
    Declaration_Sequence_Runner("TYPE x = BYTE; PROCEDURE Nop(); BEGIN END Nop;");
    Declaration_Sequence_Runner("CONST a = 3; PROCEDURE Nop(); BEGIN END Nop;");
    Declaration_Sequence_Runner("CONST a = 3; TYPE x = BYTE; VAR a: BYTE;");
    Declaration_Sequence_Runner("TYPE x = BYTE; VAR a: BYTE; PROCEDURE Nop(); BEGIN END Nop;");
    Declaration_Sequence_Runner("CONST a = 3; VAR a: BYTE; PROCEDURE Nop(); BEGIN END Nop;");
    Declaration_Sequence_Runner("CONST a = 3; TYPE x = BYTE; PROCEDURE Nop(); BEGIN END Nop;");
    Declaration_Sequence_Runner("CONST a = 3; TYPE x = BYTE; VAR a: BYTE; PROCEDURE Nop(); BEGIN END Nop;");
}

TEST(Declaration_Sequence_Tests, wrong_order) {
    Declaration_Sequence_Runner("TYPE x = BYTE; CONST a = 3;", false, true);
    Declaration_Sequence_Runner("VAR x: BYTE; CONST a = 3;", false, true);
    Declaration_Sequence_Runner("PROCEDURE Nop(); BEGIN END Nop; CONST a = 3;", false, true);
    Declaration_Sequence_Runner("VAR x: BYTE; TYPE x: BYTE;", false, true);
    Declaration_Sequence_Runner("PROCEDURE Nop(); BEGIN END Nop; TYPE x = BYTE;", false, true);
    Declaration_Sequence_Runner("PROCEDURE Nop(); BEGIN END Nop; VAR x: BYTE;", false, true);
}

#pragma clang diagnostic pop