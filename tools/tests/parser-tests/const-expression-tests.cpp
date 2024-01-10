#include "parser-tests.h"
#include "expr/integer.h"
#include "expr/bool.h"
#include "expr/nil.h"
#include "expr/float.h"

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
	auto int_value { std::dynamic_pointer_cast<expr::Integer>(
		expression.expression
	) };
	EXPECT_NE(int_value, nullptr);
	EXPECT_EQ(int_value->value, 234);

	expression.clear();
	Const_Expression_Runner test2 { "-234", expression };
	int_value = std::dynamic_pointer_cast<expr::Integer>(expression.expression);
	EXPECT_NE(int_value, nullptr);
	EXPECT_EQ(int_value->value, -234);

	expression.clear();
	Const_Expression_Runner test3 { "2.34", expression };
	auto float_value { std::dynamic_pointer_cast<expr::Float>(
		expression.expression
	) };
	EXPECT_NE(float_value, nullptr);
	EXPECT_EQ(float_value->value, 2.34);

	expression.clear();
	Const_Expression_Runner test4 { "NIL", expression };
	auto nil_value { std::dynamic_pointer_cast<expr::Nil>(
		expression.expression
	) };
	EXPECT_NE(nil_value, nullptr);

	expression.clear();
	Const_Expression_Runner test5 { "TRUE", expression };
	auto bool_value { std::dynamic_pointer_cast<expr::Bool>(
		expression.expression
	) };
	EXPECT_NE(bool_value, nullptr);
	EXPECT_TRUE(bool_value->value);

	expression.clear();
	Const_Expression_Runner test6 { "FALSE", expression };
	bool_value = std::dynamic_pointer_cast<expr::Bool>(expression.expression);
	EXPECT_NE(bool_value, nullptr);
	EXPECT_FALSE(bool_value->value);
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
	auto int_value { std::dynamic_pointer_cast<expr::Integer>(
		expression.expression
	) };
	EXPECT_NE(int_value, nullptr);
	EXPECT_EQ(int_value->value, 2);

	expression.clear();
	Const_Expression_Runner test4 { "TRUE OR FALSE", expression };
	auto bool_value { std::dynamic_pointer_cast<expr::Bool>(
		expression.expression
	) };
	EXPECT_NE(bool_value, nullptr);
	EXPECT_TRUE(bool_value->value);
}