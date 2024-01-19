#include "parser-tests.h"
#include "decl/variable.h"
#include "stmt/while.h"

using While_Statement_Runner = Parser_Value_Runner<
	stmt::Statement_Ptr, &Parser::parse_while_statement
>;

TEST(While_Statement_Tests, empty) {
	stmt::Statement_Ptr statement;
	While_Statement_Runner test1 { "", statement, true };
}

TEST(While_Statement_Tests, simple) {
	context::scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	context::scope->insert("INC", std::make_shared<decl::Procedure>());
	stmt::Statement_Ptr statement;
	While_Statement_Runner test1 { "WHILE a < 3 DO INC(a) END", statement };
	auto while_statement { std::dynamic_pointer_cast<stmt::While>(statement)};
	EXPECT_NE(while_statement, nullptr);
	if (while_statement) {
		EXPECT_EQ(while_statement->entries.size(), 1);
	}
	context::clear();
}

TEST(While_Statement_Tests, with_elsif) {
	context::scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	context::scope->insert("b", std::make_shared<decl::Variable>(nullptr));
	context::scope->insert("c", std::make_shared<decl::Variable>(nullptr));
	context::scope->insert("INC", std::make_shared<decl::Procedure>());
	stmt::Statement_Ptr statement;
	While_Statement_Runner test1 {
		"WHILE a < 3 DO INC(a) ELSIF b < 3 DO INC(b) ELSIF c < 3 DO INC(c) END",
		statement
	};
	auto while_statement { std::dynamic_pointer_cast<stmt::While>(statement)};
	EXPECT_NE(while_statement, nullptr);
	if (while_statement) {
		EXPECT_EQ(while_statement->entries.size(), 3);
	}
	context::clear();
}

TEST(While_Statement_Tests, wrong) {
	context::scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	context::scope->insert("INC", std::make_shared<decl::Variable>(nullptr));
	stmt::Statement_Ptr statement;
	While_Statement_Runner test1 { "WHILE DO", statement, true, true };
	While_Statement_Runner test2 { "WHILE a < 3 DO INC(a)", statement, true };
	While_Statement_Runner test3 { "WHILE a ELSIF", statement, true, true };
	While_Statement_Runner test4 {
		"WHILE a < 3 DO ELSIF END", statement, true, true
	};
	context::clear();
}