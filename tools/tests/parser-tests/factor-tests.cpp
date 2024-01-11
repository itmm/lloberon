#include "parser-tests.h"
#include "decl/variable.h"
#include "expr/const.h"

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
	auto int_factor { std::dynamic_pointer_cast<expr::Const>(
		factor.expression
	) };
	EXPECT_NE(int_factor, nullptr);
	if (int_factor) {
		EXPECT_TRUE(int_factor->is_int());
		if (int_factor->is_int()) { EXPECT_EQ(int_factor->int_value(), 3); }
	}

	factor.clear();
	Factor_Runner test2 { "3.241", factor };
	auto real_factor { std::dynamic_pointer_cast<expr::Const>(
		factor.expression
	) };
	EXPECT_NE(real_factor, nullptr);
	if (real_factor) {
		EXPECT_TRUE(real_factor->is_real());
		if (real_factor->is_real()) {
			EXPECT_EQ(real_factor->real_value(), 3.241);
		}
	}

	factor.clear();
	Factor_Runner test3 { "\"abc\"", factor };

	factor.clear();
	Factor_Runner test4 { "NIL", factor };
	EXPECT_EQ(factor.expression, expr::Expression::nil);

	factor.clear();
	Factor_Runner test5 { "TRUE", factor };
	auto bool_factor { std::dynamic_pointer_cast<expr::Const>(
		factor.expression
	) };
	EXPECT_NE(bool_factor, nullptr);
	if (bool_factor) {
		EXPECT_TRUE(bool_factor->is_bool());
		if (bool_factor->is_bool()) {
			EXPECT_TRUE(bool_factor->bool_value());
		}
	}

	factor.clear();
	Factor_Runner test6 { "FALSE", factor };
	bool_factor = std::dynamic_pointer_cast<expr::Const>(
		factor.expression
	);
	EXPECT_NE(bool_factor, nullptr);
	if (bool_factor) {
		EXPECT_TRUE(bool_factor->is_bool());
		if (bool_factor->is_bool()) {
			EXPECT_FALSE(bool_factor->bool_value());
		}
	}
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
}

TEST(Factor_Tests, ident) {
	Scope scope;
	scope.insert("a", std::make_shared<decl::Variable>(
		nullptr
	));
	sema::Expression factor { scope };
	Factor_Runner test1 { "a", factor };
	factor.clear();
	Factor_Runner test2 { "a(3, TRUE)", factor };
	factor.clear();
	Factor_Runner test3 { "a[3](TRUE)", factor };
}

TEST(Factor_Tests, incomplete) {
	Scope scope;
	scope.insert("a", std::make_shared<decl::Variable>(
		nullptr
	));
	sema::Expression factor { scope };
	Factor_Runner test1 { "a(3,TRUE", factor, true };
	factor.clear();
	Factor_Runner test2 { "a(3,", factor, true };
	factor.clear();
	Factor_Runner test3 { "a(3", factor, true };
	factor.clear();
	Factor_Runner test4 { "a(", factor, true };
}