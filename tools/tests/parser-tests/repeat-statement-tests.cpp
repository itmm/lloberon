#include "parser-tests.h"
#include "decl/variable.h"
#include "stmt/repeat.h"

using Repeat_Statement_Runner = Parser_Value_Runner<
	sema::Statement, &Parser::parse_repeat_statement
>;

TEST(Repeat_Statement_Tests, empty) {
	context::clear();
	sema::Statement statement;
	Repeat_Statement_Runner test1 { "", statement, true };
}

TEST(Repeat_Statement_Tests, simple) {
	context::clear();
	context::scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	sema::Statement statement;
	Repeat_Statement_Runner test1 {
		"REPEAT a := a + 1 UNTIL a > 10", statement
	};
	auto repeat_statement { std::dynamic_pointer_cast<stmt::Repeat>(
		statement.statement
	) };
	EXPECT_NE(repeat_statement, nullptr);
	if (repeat_statement) {
		EXPECT_EQ(repeat_statement->statements.size(), 1);
		EXPECT_NE(repeat_statement->condition, nullptr);
	}
}