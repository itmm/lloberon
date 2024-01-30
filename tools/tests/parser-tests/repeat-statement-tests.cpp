#include "parser-tests.h"
#include "expr/variable.h"

using Repeat_Statement_Runner = Parser_No_Void_Runner<
	stmt::Repeat_Ptr, &Parser::parse_repeat_statement
>;

TEST(Repeat_Statement_Tests, empty) {
	Repeat_Statement_Runner test1 { "", true };
}

TEST(Repeat_Statement_Tests, simple) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	Repeat_Statement_Runner test1 { "REPEAT a := a + 1 UNTIL a > 10" };
	auto repeat_statement { test1.value };
	EXPECT_NE(repeat_statement, nullptr);
	if (repeat_statement) {
		EXPECT_EQ(repeat_statement->statements.size(), 1);
		EXPECT_NE(repeat_statement->condition, nullptr);
	}
	context::clear();
}