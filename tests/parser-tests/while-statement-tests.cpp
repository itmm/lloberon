#include "expr/call.h"
#include "expr/variable.h"
#include "parser-tests.h"
#include "stmt/while.h"
#include "decl/procedure.h"

using While_Statement_Runner = Parser_No_Void_Runner<
	stmt::While_Ptr, &Parser::parse_while_statement
>;

TEST(While_Statement_Tests, empty) {
	While_Statement_Runner test1 { "", true };
}

TEST(While_Statement_Tests, simple) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("INC", std::make_shared<decl::Procedure>());
	While_Statement_Runner test1 { "WHILE a < 3 DO INC(a) END" };
	auto while_statement { test1.value };
	EXPECT_NE(while_statement, nullptr);
	if (while_statement) {
		EXPECT_EQ(while_statement->entries.size(), 1);
	}
	context::clear();
}

TEST(While_Statement_Tests, with_elsif) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("b", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("c", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("INC", std::make_shared<decl::Procedure>());
	While_Statement_Runner test1 {
		"WHILE a < 3 DO INC(a) ELSIF b < 3 DO INC(b) ELSIF c < 3 DO INC(c) END"
	};
	auto while_statement { test1.value };
	EXPECT_NE(while_statement, nullptr);
	if (while_statement) {
		EXPECT_EQ(while_statement->entries.size(), 3);
	}
	context::clear();
}

TEST(While_Statement_Tests, wrong) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("INC", std::make_shared<decl::Procedure>());
	While_Statement_Runner test1 { "WHILE DO", true, true };
	While_Statement_Runner test2 { "WHILE a < 3 DO INC(a)", true };
	While_Statement_Runner test3 { "WHILE a ELSIF", true, true };
	While_Statement_Runner test4 { "WHILE a < 3 DO ELSIF END", true, true };
	context::clear();
}