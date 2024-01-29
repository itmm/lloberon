#include "parser-tests.h"
#include "stmt/if.h"
#include "expr/variable.h"

using If_Statement_Runner = Parser_No_Void_Runner<
	stmt::If_Ptr, &Parser::parse_if_statement
>;

TEST(If_Statement_Tests, empty) {
	If_Statement_Runner test1 { "", true };
}

void expect_entries_count(const stmt::If_Ptr& if_statement, int count) {
	EXPECT_NE(if_statement, nullptr);
	if (if_statement) {
		EXPECT_EQ(if_statement->entries.size(), count);
	}
}

TEST(If_Statement_Tests, simple) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("b", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("cond", std::make_shared<expr::Variable>(nullptr));
	If_Statement_Runner test1 { "IF cond THEN a := 1; b := TRUE END" };
	expect_entries_count(test1.value, 1);
	context::clear();
}

TEST(If_Statement_Tests, with_else) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("b", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("cond", std::make_shared<expr::Variable>(nullptr));
	If_Statement_Runner test1 {
		"IF cond THEN a := 1 ELSE a := 2; b := TRUE END"
	};
	expect_entries_count(test1.value, 2);
	context::clear();
}

TEST(If_Statement_Tests, with_elsif) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	If_Statement_Runner test1 {
		"IF a < 3 THEN a := -1 ELSIF a > 3 THEN a := 1 ELSE a := 0 END"
	};
	expect_entries_count(test1.value, 3);
	context::clear();
}