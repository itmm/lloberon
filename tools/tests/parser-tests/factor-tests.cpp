#include "parser-tests.h"
#include "decl/variable.h"
#include "expr/const.h"
#include "const-tests.h"
#include "type-tests.h"

using Factor_Runner = Parser_Value_Runner<
	sema::Expression, &Parser::parse_factor
>;

TEST(Factor_Tests, empty) {
	Scope scope;
	sema::Expression factor { scope };
	Factor_Runner("", factor, true);
}

TEST(Factor_Tests, literals) {
	Scope scope;
	sema::Expression factor { scope };
	Factor_Runner test1 { "3", factor };
	expect_int_value(factor.expression, 3);

	Factor_Runner test2 { "3.241", factor };
	expect_real_value(factor.expression, 3.241);

	Factor_Runner test3 { "\"abc\"", factor };
	expect_string_value(factor.expression, "abc");

	Factor_Runner test4 { "NIL", factor };
	EXPECT_EQ(factor.expression, expr::Expression::nil);

	Factor_Runner test5 { "TRUE", factor };
	expect_bool_value(factor.expression, true);

	Factor_Runner test6 { "FALSE", factor };
	expect_bool_value(factor.expression, false);
}

TEST(Factor_Tests, set) {
	Scope scope;
	sema::Expression factor { scope };
	Factor_Runner test1 { "{3..5}", factor };
}

TEST(Factor_Tests, grouped) {
	Scope scope;
	sema::Expression factor { scope };
	Factor_Runner test1 { "(3 + 4)", factor };
	expect_int_value(factor.expression, 7);
}

TEST(Factor_Tests, ident) {
	Scope base;
	decl::Type::register_base_types(base);
	Scope scope { &base };
	sema::Type type { scope };
	Type_Runner type_runner { "ARRAY 10 OF PROCEDURE(x: BOOLEAN)", type };
	scope.insert("a", std::make_shared<decl::Variable>(type.type));
	scope.insert("f", std::make_shared<decl::Procedure>());
	sema::Expression factor { scope };
	Factor_Runner test1 { "a", factor };
	Factor_Runner test2 { "f(3, TRUE)", factor };
	Factor_Runner test3 { "a[3](TRUE)", factor };
}

TEST(Factor_Tests, not) {
	Scope scope;
	sema::Expression factor { scope };
	Factor_Runner test1 { "~FALSE", factor };
	auto value { expr::Const::as_const(factor.expression) };
	EXPECT_NE(value, nullptr);
	if (value) {
		EXPECT_TRUE(value->is_bool() && value->bool_value());
	}
}

TEST(Factor_Tests, incomplete) {
	Scope scope;
	scope.insert("a", std::make_shared<decl::Procedure>());
	sema::Expression factor { scope };
	Factor_Runner test1 { "a(3,TRUE", factor, true };
	Factor_Runner test2 { "a(3,", factor, true };
	Factor_Runner test3 { "a(3", factor, true };
	Factor_Runner test4 { "a(", factor, true };
}