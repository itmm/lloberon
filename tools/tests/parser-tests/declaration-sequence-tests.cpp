#include "parser-tests.h"
#include "decl/const.h"
#include "decl/type.h"
#include "const-tests.h"

using Declaration_Sequence_Runner = Parser_Value_Runner<
	Scope, &Parser::parse_declaration_sequence
>;

TEST(Declaration_Sequence_Tests, empty) {
	Scope scope;
	Declaration_Sequence_Runner test1 { "", scope };
}

TEST(Declaration_Sequence_Tests, single) {
	Scope base;
	Scope scope { &base };
	decl::Type::register_base_types(base);
	Declaration_Sequence_Runner test1 { "CONST a = 3;", scope };
	expect_int_value(decl::Const::as_const(scope.lookup("a")), 3);

	scope.clear();
	Declaration_Sequence_Runner test2 {
		"TYPE image = ARRAY 10 OF INTEGER;", scope
	};

	scope.clear();
	Declaration_Sequence_Runner test3 { "VAR a: INTEGER;", scope };

	scope.clear();
	Declaration_Sequence_Runner test4 {
		"PROCEDURE Nop(); BEGIN END Nop;", scope
	};
}

TEST(Declaration_Sequence_Tests, multiple) {
	Scope base;
	Scope scope { &base };
	decl::Type::register_base_types(base);
	Declaration_Sequence_Runner test1 { "CONST a = 3; b = 4;", scope };
	expect_int_value(decl::Const::as_const(scope.lookup("a")), 3);
	expect_int_value(decl::Const::as_const(scope.lookup("b")), 4);

	scope.clear();
	Declaration_Sequence_Runner test2 { "TYPE X = INTEGER; Y = BYTE;", scope };

	scope.clear();
	Declaration_Sequence_Runner test3 { "VAR a: INTEGER; b: BYTE;", scope };

	scope.clear();
	Declaration_Sequence_Runner test4 {
		"PROCEDURE Nop(); BEGIN END Nop; PROCEDURE Nop2(); BEGIN END Nop2;",
		scope
	};
}

TEST(Declaration_Sequence_Tests, multiple_types) {
	Scope base;
	Scope scope { &base };
	decl::Type::register_base_types(base);
	Declaration_Sequence_Runner test1 { "CONST a = 3; TYPE x = BYTE;", scope };
	expect_int_value(decl::Const::as_const(scope.lookup("a")), 3);

	scope.clear();
	Declaration_Sequence_Runner test2 { "TYPE x = BYTE; VAR a: BYTE;", scope };

	scope.clear();
	Declaration_Sequence_Runner test3 {
		"VAR a: BYTE; PROCEDURE Nop(); BEGIN END Nop;", scope
	};

	scope.clear();
	Declaration_Sequence_Runner test4 { "CONST a = 3; VAR b: BYTE;", scope };
	expect_int_value(decl::Const::as_const(scope.lookup("a")), 3);

	scope.clear();
	Declaration_Sequence_Runner test5 {
		"TYPE x = BYTE; PROCEDURE Nop(); BEGIN END Nop;", scope
	};

	scope.clear();
	Declaration_Sequence_Runner test6 {
		"CONST a = 3; PROCEDURE Nop(); BEGIN END Nop;", scope
	};
	expect_int_value(decl::Const::as_const(scope.lookup("a")), 3);

	scope.clear();
	Declaration_Sequence_Runner test7 {
		"CONST a = 3; TYPE x = BYTE; VAR b: BYTE;", scope
	};
	expect_int_value(decl::Const::as_const(scope.lookup("a")), 3);

	scope.clear();
	Declaration_Sequence_Runner test8 {
		"TYPE x = BYTE; VAR a: BYTE; PROCEDURE Nop(); BEGIN END Nop;", scope
	};

	scope.clear();
	Declaration_Sequence_Runner test9 {
		"CONST a = 3; VAR b: BYTE; PROCEDURE Nop(); BEGIN END Nop;", scope
	};
	expect_int_value(decl::Const::as_const(scope.lookup("a")), 3);

	scope.clear();
	Declaration_Sequence_Runner test10 {
		"CONST a = 3; TYPE x = BYTE; PROCEDURE Nop(); BEGIN END Nop;", scope
	};
	expect_int_value(decl::Const::as_const(scope.lookup("a")), 3);

	scope.clear();
	Declaration_Sequence_Runner test11 {
		"CONST a = 3; TYPE x = BYTE; VAR b: BYTE; "
		"PROCEDURE Nop(); BEGIN END Nop;",
		scope
	};
	expect_int_value(decl::Const::as_const(scope.lookup("a")), 3);
}

TEST(Declaration_Sequence_Tests, wrong_order) {
	Scope base;
	Scope scope { &base };
	decl::Type::register_base_types(base);
	Declaration_Sequence_Runner test1 {
		"TYPE x = BYTE; CONST a = 3;", scope, false, true
	};

	scope.clear();
	Declaration_Sequence_Runner test2 {
		"VAR x: BYTE; CONST a = 3;", scope, false, true
	};

	scope.clear();
	Declaration_Sequence_Runner test3 {
		"PROCEDURE Nop(); BEGIN END Nop; CONST a = 3;", scope, false, true
	};

	scope.clear();
	Declaration_Sequence_Runner test4 {
		"VAR x: BYTE; TYPE x: BYTE;", scope, false, true
	};

	scope.clear();
	Declaration_Sequence_Runner test5 {
		"PROCEDURE Nop(); BEGIN END Nop; TYPE x = BYTE;", scope, false, true
	};

	scope.clear();
	Declaration_Sequence_Runner test6 {
		"PROCEDURE Nop(); BEGIN END Nop; VAR x: BYTE;", scope, false, true
	};
}