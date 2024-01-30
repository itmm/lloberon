#include "parser-tests.h"
#include "expr/variable.h"

using Statement_Sequence_Runner = Parser_No_Void_Runner<
	stmt::Statement_Sequence, &Parser::parse_statement_sequence
>;

TEST(Statement_Sequence_Tests, empty) {
	Statement_Sequence_Runner test1 { "" };
}

TEST(Statement_Sequence_Tests, single) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	Statement_Sequence_Runner test1 { "a := 3" };
	context::clear();
}

TEST(Statement_Sequence_Tests, multiple) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("b", std::make_shared<expr::Variable>(nullptr));
	Statement_Sequence_Runner test1 { "a := 3;" };
	Statement_Sequence_Runner test2 { "a := 3; b := 4" };
	Statement_Sequence_Runner test3 { "a := 3; b := 4;" };
	context::clear();
}