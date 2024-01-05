#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-raii"

#include "parser-tests.h"

using Declaration_Sequence_Runner = Parser_Value_Runner<
    sema::Declaration_Sequence, &Parser::parse_declaration_sequence
>;

TEST(Declaration_Sequence_Tests, empty) {
    Scope scope;
    sema::Declaration_Sequence declaration_sequence { scope };
    Declaration_Sequence_Runner("", declaration_sequence);
}

TEST(Declaration_Sequence_Tests, single) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
        "INTEGER", Base_Type_Declaration::bt_INTEGER
    });
    sema::Declaration_Sequence declaration_sequence { scope };
    Declaration_Sequence_Runner("CONST a = 3;", declaration_sequence);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("TYPE image = ARRAY 10 OF INTEGER;", declaration_sequence);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("VAR a: INTEGER;", declaration_sequence);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("PROCEDURE Nop(); BEGIN END Nop;", declaration_sequence);
}

TEST(Declaration_Sequence_Tests, multiple) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
            "BYTE", Base_Type_Declaration::bt_BYTE
    });
    scope.insert(new Base_Type_Declaration {
            "INTEGER", Base_Type_Declaration::bt_INTEGER
    });
    sema::Declaration_Sequence declaration_sequence { scope };
    Declaration_Sequence_Runner("CONST a = 3; b = 4;", declaration_sequence);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("TYPE X = INTEGER; Y = BYTE;", declaration_sequence);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("VAR a: INTEGER; b: BYTE;", declaration_sequence);

    declaration_sequence.clear();
    Declaration_Sequence_Runner(
        "PROCEDURE Nop(); BEGIN END Nop; PROCEDURE Nop2(); BEGIN END Nop2;",
        declaration_sequence
    );
}

TEST(Declaration_Sequence_Tests, multiple_types) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
            "BYTE", Base_Type_Declaration::bt_BYTE
    });
    sema::Declaration_Sequence declaration_sequence { scope };
    Declaration_Sequence_Runner("CONST a = 3; TYPE x = BYTE;", declaration_sequence);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("TYPE x = BYTE; VAR a: BYTE;", declaration_sequence);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("VAR a: BYTE; PROCEDURE Nop(); BEGIN END Nop;", declaration_sequence);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("CONST a = 3; VAR a: BYTE;", declaration_sequence);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("TYPE x = BYTE; PROCEDURE Nop(); BEGIN END Nop;", declaration_sequence);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("CONST a = 3; PROCEDURE Nop(); BEGIN END Nop;", declaration_sequence);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("CONST a = 3; TYPE x = BYTE; VAR a: BYTE;", declaration_sequence);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("TYPE x = BYTE; VAR a: BYTE; PROCEDURE Nop(); BEGIN END Nop;", declaration_sequence);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("CONST a = 3; VAR a: BYTE; PROCEDURE Nop(); BEGIN END Nop;", declaration_sequence);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("CONST a = 3; TYPE x = BYTE; PROCEDURE Nop(); BEGIN END Nop;", declaration_sequence);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("CONST a = 3; TYPE x = BYTE; VAR a: BYTE; PROCEDURE Nop(); BEGIN END Nop;", declaration_sequence);
}

TEST(Declaration_Sequence_Tests, wrong_order) {
    Scope scope;
    scope.insert(new Base_Type_Declaration {
            "BYTE", Base_Type_Declaration::bt_BYTE
    });
    sema::Declaration_Sequence declaration_sequence { scope };
    Declaration_Sequence_Runner("TYPE x = BYTE; CONST a = 3;", declaration_sequence, false, true);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("VAR x: BYTE; CONST a = 3;", declaration_sequence, false, true);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("PROCEDURE Nop(); BEGIN END Nop; CONST a = 3;", declaration_sequence, false, true);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("VAR x: BYTE; TYPE x: BYTE;", declaration_sequence, false, true);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("PROCEDURE Nop(); BEGIN END Nop; TYPE x = BYTE;", declaration_sequence, false, true);

    declaration_sequence.clear();
    Declaration_Sequence_Runner("PROCEDURE Nop(); BEGIN END Nop; VAR x: BYTE;", declaration_sequence, false, true);
}

#pragma clang diagnostic pop