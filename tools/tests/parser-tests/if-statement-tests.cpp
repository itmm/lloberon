#include "parser-tests.h"
#include "decl/variable.h"
#include "stmt/if.h"

using If_Statement_Runner = Parser_Value_Runner<
	stmt::Statement_Ptr, &Parser::parse_if_statement
>;

TEST(If_Statement_Tests, empty) {
	context::clear();
	stmt::Statement_Ptr if_statement;
	If_Statement_Runner test1 { "", if_statement, true };
}

void expect_entries_count(const stmt::Statement_Ptr& statement, int count) {
	auto if_statement { std::dynamic_pointer_cast<stmt::If>(statement) };
	EXPECT_NE(if_statement, nullptr);
	if (if_statement) {
		EXPECT_EQ(if_statement->entries.size(), count);
	}
}

TEST(If_Statement_Tests, simple) {
	context::clear();
	context::scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	context::scope->insert("b", std::make_shared<decl::Variable>(nullptr));
	context::scope->insert("cond", std::make_shared<decl::Variable>(nullptr));
	stmt::Statement_Ptr statement;
	If_Statement_Runner test1 {
		"IF cond THEN a := 1; b := TRUE END", statement
	};
	expect_entries_count(statement, 1);
}

TEST(If_Statement_Tests, with_else) {
	context::clear();
	context::scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	context::scope->insert("b", std::make_shared<decl::Variable>(nullptr));
	context::scope->insert("cond", std::make_shared<decl::Variable>(nullptr));
	stmt::Statement_Ptr statement;
	If_Statement_Runner test1 {
		"IF cond THEN a := 1 ELSE a := 2; b := TRUE END", statement
	};
	expect_entries_count(statement, 2);
}

TEST(If_Statement_Tests, with_elsif) {
	context::clear();
	context::scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	stmt::Statement_Ptr statement;
	If_Statement_Runner test1 {
		"IF a < 3 THEN a := -1 ELSIF a > 3 THEN a := 1 ELSE a := 0 END",
		statement
	};
	expect_entries_count(statement, 3);
}