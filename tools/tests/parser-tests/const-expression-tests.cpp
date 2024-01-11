#include "expr/const.h"
#include "parser-tests.h"

using Const_Expression_Runner = Parser_Value_Runner<
	sema::Const_Expression, &Parser::parse_const_expression
>;

TEST(Const_Expression_Tests, empty) {
	Scope scope;
	sema::Const_Expression expression { scope };
	Const_Expression_Runner test1 { "", expression, true };
	EXPECT_EQ(expression.expression, nullptr);
}

TEST(Const_Expression_Tests, literals) {
	Scope scope;
	sema::Const_Expression expression { scope };

	Const_Expression_Runner test1 { "234", expression };
	auto int_value { std::dynamic_pointer_cast<expr::Const>(
		expression.expression
	) };
	EXPECT_NE(int_value, nullptr);
	if (int_value) {
		EXPECT_TRUE(int_value->is_int());
		if (int_value->is_int()) { EXPECT_EQ(int_value->int_value(), 234); }
	}

	expression.clear();
	Const_Expression_Runner test2 { "-234", expression };
	int_value = std::dynamic_pointer_cast<expr::Const>(expression.expression);
	EXPECT_NE(int_value, nullptr);
	if (int_value) {
		EXPECT_TRUE(int_value->is_int());
		if (int_value->is_int()) { EXPECT_EQ(int_value->int_value(), -234); }
	}

	expression.clear();
	Const_Expression_Runner test3 { "2.34", expression };
	auto real_value { std::dynamic_pointer_cast<expr::Const>(
		expression.expression
	) };
	EXPECT_NE(real_value, nullptr);
	if (real_value) {
		EXPECT_TRUE(real_value->is_real());
		if (real_value->is_real()) {
			EXPECT_EQ(real_value->real_value(), 2.34);
		}
	}

	expression.clear();
	Const_Expression_Runner test5 { "TRUE", expression };
	auto bool_value { std::dynamic_pointer_cast<expr::Const>(
		expression.expression
	) };
	EXPECT_NE(bool_value, nullptr);
	if (bool_value) {
		EXPECT_TRUE(bool_value->is_bool());
		if (bool_value->is_bool()) { EXPECT_TRUE(bool_value->bool_value()); }
	}

	expression.clear();
	Const_Expression_Runner test6 { "FALSE", expression };
	bool_value = std::dynamic_pointer_cast<expr::Const>(expression.expression);
	EXPECT_NE(bool_value, nullptr);
	if (bool_value) {
		EXPECT_TRUE(bool_value->is_bool());
		if (bool_value->is_bool()) { EXPECT_FALSE(bool_value->bool_value()); }
	}
}

TEST(Const_Expression_Tests, expressions) {
	Scope scope;
	sema::Const_Expression expression { scope };
	// TODO: more tests
	Const_Expression_Runner test1 { "3 + 4 * 2", expression };

	expression.clear();
	Const_Expression_Runner test2 { "2 < 4 # FALSE", expression };

	expression.clear();
	Const_Expression_Runner test3 { "5 - 3", expression };
	auto int_value { std::dynamic_pointer_cast<expr::Const>(
		expression.expression
	) };
	EXPECT_NE(int_value, nullptr);
	if (int_value) {
		EXPECT_TRUE(int_value->is_int());
		if (int_value->is_int()) { EXPECT_EQ(int_value->int_value(), 2); }
	}

	expression.clear();
	Const_Expression_Runner test4 { "TRUE OR FALSE", expression };
	auto bool_value { std::dynamic_pointer_cast<expr::Const>(
		expression.expression
	) };
	EXPECT_NE(bool_value, nullptr);
	if (bool_value) {
		EXPECT_TRUE(bool_value->is_bool());
		if (bool_value->is_bool()) { EXPECT_TRUE(bool_value->bool_value()); }
	}
}