#include "parser-tests.h"
#include "expr/variable.h"

using Statement_Runner = Parser_No_Void_Runner<
	stmt::Statement_Ptr, &Parser::parse_statement
>;

TEST(Statement_Tests, empty) {
	Statement_Runner test1 { "" };
	EXPECT_EQ(test1.value, nullptr);
}

TEST(Statement_Tests, single) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("b", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("i", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("cond", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("f", std::make_shared<decl::Procedure>());
	Statement_Runner test1 { "a := 3" };
	Statement_Runner test2 { "f(2, 3)" };
	Statement_Runner test3 { "IF b THEN a := 3 END" };
	Statement_Runner test4 { "CASE cond OF 3: a := 3 END" };
	Statement_Runner test5 { "WHILE cond DO END" };
	Statement_Runner test6 { "REPEAT UNTIL cond" };
	Statement_Runner test7 { "FOR i := 1 TO 10 DO END" };
	context::clear();
}

TEST(Statement_Tests, invalid) {
	Statement_Runner test1 { "3", false, true };
}