#include "parser-tests.h"
#include "stmt/for.h"
#include "const-tests.h"

using For_Statement_Runner = Parser_No_Void_Runner<
	stmt::For_Ptr, &Parser::parse_for_statement
>;

TEST(For_Statement_Tests, empty) {
	For_Statement_Runner test1 { "", true };
}

TEST(For_Statement_Tests, simple) {
	auto var { std::make_shared<expr::Variable>(nullptr) };
	context::scope->insert("a", var);
	context::scope->insert("x", std::make_shared<expr::Variable>(nullptr));
	For_Statement_Runner test1 { "FOR a := 1 TO 3 DO x := x + a END" };
	auto for_statement { test1.value };
	EXPECT_NE(for_statement, nullptr);
	if (for_statement) {
		EXPECT_EQ(for_statement->variable, var);
		expect_int_value(for_statement->begin, 1);
		expect_int_value(for_statement->end, 3);
		expect_int_value(for_statement->increment, 1);
		EXPECT_EQ(for_statement->statements.size(), 1);
	}
	context::clear();
}

TEST(For_Statement_Tests, with_step) {
	auto var { std::make_shared<expr::Variable>(nullptr) };
	context::scope->insert("a", var);
	context::scope->insert("x", std::make_shared<expr::Variable>(nullptr));
	For_Statement_Runner test1 { "FOR a := 1 TO 10 BY 2 DO x := x + a END" };
	auto for_statement { test1.value };
	EXPECT_NE(for_statement, nullptr);
	if (for_statement) {
		EXPECT_EQ(for_statement->variable, var);
		expect_int_value(for_statement->begin, 1);
		expect_int_value(for_statement->end, 10);
		expect_int_value(for_statement->increment, 2);
		EXPECT_EQ(for_statement->statements.size(), 1);
	}
	context::clear();
}

TEST(For_Statement_Tests, with_stepdown) {
	auto var { std::make_shared<expr::Variable>(nullptr) };
	context::scope->insert("a", var);
	context::scope->insert("x", std::make_shared<expr::Variable>(nullptr));
	For_Statement_Runner test1 { "FOR a := 10 TO 0 BY -2 DO x := x + a END" };
	auto for_statement { test1.value };
	EXPECT_NE(for_statement, nullptr);
	if (for_statement) {
		EXPECT_EQ(for_statement->variable, var);
		expect_int_value(for_statement->begin, 10);
		expect_int_value(for_statement->end, 0);
		expect_int_value(for_statement->increment, -2);
		EXPECT_EQ(for_statement->statements.size(), 1);
	}
	context::clear();
}

TEST(For_Statement_Tests, wrong) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	For_Statement_Runner test1 { "FOR", true };
	For_Statement_Runner test2 { "FOR a", true };
	For_Statement_Runner test3 { "FOR :=", true, true };
	For_Statement_Runner test4 { "FOR a :=", true };
	For_Statement_Runner test5 { "FOR a 1", true, true };
	For_Statement_Runner test6 { "FOR a := 1", true };
	For_Statement_Runner test7 { "FOR a := 1 TO", true };
	For_Statement_Runner test8 { "FOR a := 1 TO 10", true };
	For_Statement_Runner test9 { "FOR a := 1 10", true, true };
	For_Statement_Runner test10 { "FOR a := 1 TO 10 DO", true };
	For_Statement_Runner test11 { "FOR a := 1 TO 10 END", true, true };
	For_Statement_Runner test12 { "FOR a := 1 TO 10 BY DO", true, true };
	context::clear();
}