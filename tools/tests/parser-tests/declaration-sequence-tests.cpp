#include "parser-tests.h"
#include "decl/type.h"

using Declaration_Sequence_Runner = Parser_Value_Runner<
	sema::Declaration_Sequence, &Parser::parse_declaration_sequence
>;

TEST(Declaration_Sequence_Tests, empty) {
	Scope scope;
	sema::Declaration_Sequence declaration_sequence { scope };
	Declaration_Sequence_Runner test1 { "", declaration_sequence };
}

TEST(Declaration_Sequence_Tests, single) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Declaration_Sequence declaration_sequence { scope };
	Declaration_Sequence_Runner test1 { "CONST a = 3;", declaration_sequence };

	declaration_sequence.clear();
	Declaration_Sequence_Runner test2 {
		"TYPE image = ARRAY 10 OF INTEGER;", declaration_sequence
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test3 {
		"VAR a: INTEGER;", declaration_sequence
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test4 {
		"PROCEDURE Nop(); BEGIN END Nop;", declaration_sequence
	};
}

TEST(Declaration_Sequence_Tests, multiple) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Declaration_Sequence declaration_sequence { scope };
	Declaration_Sequence_Runner test1 {
		"CONST a = 3; b = 4;", declaration_sequence
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test2 {
		"TYPE X = INTEGER; Y = BYTE;", declaration_sequence
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test3 {
		"VAR a: INTEGER; b: BYTE;", declaration_sequence
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test4 {
		"PROCEDURE Nop(); BEGIN END Nop; PROCEDURE Nop2(); BEGIN END Nop2;",
		declaration_sequence
	};
}

TEST(Declaration_Sequence_Tests, multiple_types) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Declaration_Sequence declaration_sequence { scope };
	Declaration_Sequence_Runner test1 {
		"CONST a = 3; TYPE x = BYTE;", declaration_sequence
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test2 {
		"TYPE x = BYTE; VAR a: BYTE;", declaration_sequence
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test3 {
		"VAR a: BYTE; PROCEDURE Nop(); BEGIN END Nop;", declaration_sequence
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test4 {
		"CONST a = 3; VAR a: BYTE;", declaration_sequence
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test5 {
		"TYPE x = BYTE; PROCEDURE Nop(); BEGIN END Nop;", declaration_sequence
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test6 {
		"CONST a = 3; PROCEDURE Nop(); BEGIN END Nop;", declaration_sequence
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test7 {
		"CONST a = 3; TYPE x = BYTE; VAR a: BYTE;", declaration_sequence
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test8 {
		"TYPE x = BYTE; VAR a: BYTE; PROCEDURE Nop(); BEGIN END Nop;",
		declaration_sequence
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test9 {
		"CONST a = 3; VAR a: BYTE; PROCEDURE Nop(); BEGIN END Nop;",
		declaration_sequence
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test10 {
		"CONST a = 3; TYPE x = BYTE; PROCEDURE Nop(); BEGIN END Nop;",
		declaration_sequence
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test11 {
		"CONST a = 3; TYPE x = BYTE; VAR a: BYTE; "
		"PROCEDURE Nop(); BEGIN END Nop;",
		declaration_sequence
	};
}

TEST(Declaration_Sequence_Tests, wrong_order) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Declaration_Sequence declaration_sequence { scope };
	Declaration_Sequence_Runner test1 {
		"TYPE x = BYTE; CONST a = 3;", declaration_sequence, false, true
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test2 {
		"VAR x: BYTE; CONST a = 3;", declaration_sequence, false, true
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test3 {
		"PROCEDURE Nop(); BEGIN END Nop; CONST a = 3;",
		declaration_sequence, false, true
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test4 {
		"VAR x: BYTE; TYPE x: BYTE;", declaration_sequence, false, true
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test5 {
		"PROCEDURE Nop(); BEGIN END Nop; TYPE x = BYTE;",
		declaration_sequence, false, true
	};

	declaration_sequence.clear();
	Declaration_Sequence_Runner test6 {
		"PROCEDURE Nop(); BEGIN END Nop; VAR x: BYTE;",
		declaration_sequence, false, true
	};
}