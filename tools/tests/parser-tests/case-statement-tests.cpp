#include "parser-tests.h"
#include "expr/variable.h"

using Case_Statement_Runner = Parser_No_Void_Runner<
	stmt::Statement_Ptr, &Parser::parse_case_statement
>;

TEST(Case_Statetment_Tests, empty) {
	Case_Statement_Runner("", true);
}

TEST(Case_Statement_Tests, single) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("x", std::make_shared<expr::Variable>(nullptr));
	Case_Statement_Runner test1 { "", true };
	Case_Statement_Runner test2 { "CASE a OF 3: x := 1 END" };
	context::clear();
}

TEST(Case_Statement_Tests, multiple) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("x", std::make_shared<expr::Variable>(nullptr));
	Case_Statement_Runner test1 { "CASE a OF 3: x := 1 | 2, 4: x := 2 END" };
	context::clear();
}

TEST(Case_Statement_Tests, wrong) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	Case_Statement_Runner test1 { "CASE OF", true, true };
	Case_Statement_Runner test2 { "CASE a 3:", true, true };
	Case_Statement_Runner test3 { "CASE a OF END", true, true };
	Case_Statement_Runner test4 { "CASE a OF 3: |", true };
	context::clear();
}