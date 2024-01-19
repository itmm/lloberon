#include "parser-tests.h"
#include "decl/const.h"
#include "const-tests.h"

using Declaration_Sequence_Runner = Parser_String_Runner<
	&Parser::parse_declaration_sequence
>;

TEST(Declaration_Sequence_Tests, empty) {
	Declaration_Sequence_Runner test1 { "" };
}

TEST(Declaration_Sequence_Tests, single) {
	auto base { std::make_shared<Scope>() };
	context::scope = std::make_shared<Scope>(base);
	base->register_base_types();
	Declaration_Sequence_Runner test1 { "CONST a = 3;" };
	expect_int_value(decl::Const::as_const(context::scope->lookup("a")), 3);
	context::scope->clear();

	Declaration_Sequence_Runner test2 { "TYPE image = ARRAY 10 OF INTEGER;" };
	context::scope->clear();

	Declaration_Sequence_Runner test3 { "VAR a: INTEGER;" };
	context::scope->clear();

	Declaration_Sequence_Runner test4 { "PROCEDURE Nop(); BEGIN END Nop;" };
	context::clear();
}

TEST(Declaration_Sequence_Tests, multiple) {
	auto base { std::make_shared<Scope>() };
	context::scope = std::make_shared<Scope>(base);
	base->register_base_types();
	Declaration_Sequence_Runner test1 { "CONST a = 3; b = 4;" };
	expect_int_value(decl::Const::as_const(context::scope->lookup("a")), 3);
	expect_int_value(decl::Const::as_const(context::scope->lookup("b")), 4);
	context::scope->clear();

	Declaration_Sequence_Runner test2 { "TYPE X = INTEGER; Y = BYTE;" };
	context::scope->clear();

	Declaration_Sequence_Runner test3 { "VAR a: INTEGER; b: BYTE;" };
	context::scope->clear();

	Declaration_Sequence_Runner test4 {
		"PROCEDURE Nop(); BEGIN END Nop; PROCEDURE Nop2(); BEGIN END Nop2;"
	};
	context::clear();
}

TEST(Declaration_Sequence_Tests, multiple_types) {
	auto base { std::make_shared<Scope>() };
	context::scope = std::make_shared<Scope>(base);
	base->register_base_types();
	Declaration_Sequence_Runner test1 { "CONST a = 3; TYPE x = BYTE;" };
	expect_int_value(decl::Const::as_const(context::scope->lookup("a")), 3);
	context::scope->clear();

	Declaration_Sequence_Runner test2 { "TYPE x = BYTE; VAR a: BYTE;" };
	context::scope->clear();

	Declaration_Sequence_Runner test3 {
		"VAR a: BYTE; PROCEDURE Nop(); BEGIN END Nop;"
	};
	context::scope->clear();

	Declaration_Sequence_Runner test4 { "CONST a = 3; VAR b: BYTE;" };
	expect_int_value(decl::Const::as_const(context::scope->lookup("a")), 3);
	context::scope->clear();

	Declaration_Sequence_Runner test5 {
		"TYPE x = BYTE; PROCEDURE Nop(); BEGIN END Nop;"
	};
	context::scope->clear();

	Declaration_Sequence_Runner test6 {
		"CONST a = 3; PROCEDURE Nop(); BEGIN END Nop;"
	};
	expect_int_value(decl::Const::as_const(context::scope->lookup("a")), 3);
	context::scope->clear();

	Declaration_Sequence_Runner test7 {
		"CONST a = 3; TYPE x = BYTE; VAR b: BYTE;"
	};
	expect_int_value(decl::Const::as_const(context::scope->lookup("a")), 3);
	context::scope->clear();

	Declaration_Sequence_Runner test8 {
		"TYPE x = BYTE; VAR a: BYTE; PROCEDURE Nop(); BEGIN END Nop;"
	};
	context::scope->clear();

	Declaration_Sequence_Runner test9 {
		"CONST a = 3; VAR b: BYTE; PROCEDURE Nop(); BEGIN END Nop;"
	};
	expect_int_value(decl::Const::as_const(context::scope->lookup("a")), 3);
	context::scope->clear();

	Declaration_Sequence_Runner test10 {
		"CONST a = 3; TYPE x = BYTE; PROCEDURE Nop(); BEGIN END Nop;"
	};
	expect_int_value(decl::Const::as_const(context::scope->lookup("a")), 3);
	context::scope->clear();

	Declaration_Sequence_Runner test11 {
		"CONST a = 3; TYPE x = BYTE; VAR b: BYTE; "
		"PROCEDURE Nop(); BEGIN END Nop;"
	};
	expect_int_value(decl::Const::as_const(context::scope->lookup("a")), 3);
	context::clear();
}

TEST(Declaration_Sequence_Tests, shadowing) {
	context::clear();
	auto base { std::make_shared<Scope>() };
	base->register_base_types();
	context::scope = std::make_shared<Scope>(base);
	Declaration_Sequence_Runner test1 {
		"CONST a = 42; PROCEDURE f(a: INTEGER): INTEGER; RETURN a END f;"
	};

	context::scope->clear();
	Declaration_Sequence_Runner test2 {
		"CONST a = 3; PROCEDURE f(): INTEGER; CONST a = 42; RETURN a END f;"
	};
}

TEST(Declaration_Sequence_Tests, wrong_order) {
	context::clear();
	auto base { std::make_shared<Scope>() };
	context::scope = std::make_shared<Scope>(base);
	base->register_base_types();

	Declaration_Sequence_Runner test1 {
		"TYPE x = BYTE; CONST a = 3;", false, true
	};

	context::scope->clear();
	Declaration_Sequence_Runner test2 {
		"VAR x: BYTE; CONST a = 3;", false, true
	};

	context::scope->clear();
	Declaration_Sequence_Runner test3 {
		"PROCEDURE Nop(); BEGIN END Nop; CONST a = 3;", false, true
	};

	context::scope->clear();
	Declaration_Sequence_Runner test4 {
		"VAR x: BYTE; TYPE x: BYTE;", false, true
	};

	context::scope->clear();
	Declaration_Sequence_Runner test5 {
		"PROCEDURE Nop(); BEGIN END Nop; TYPE x = BYTE;", false, true
	};

	context::scope->clear();
	Declaration_Sequence_Runner test6 {
		"PROCEDURE Nop(); BEGIN END Nop; VAR x: BYTE;", false, true
	};
}