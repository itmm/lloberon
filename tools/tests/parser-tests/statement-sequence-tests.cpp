#include "parser-tests.h"

using Statement_Sequence_Runner = Parser_Value_Runner<
	stmt::Statement_Sequence, &Parser::parse_statement_sequence
>;

TEST(Statement_Sequence_Tests, empty) {
	stmt::Statement_Sequence statement_sequence;
	Statement_Sequence_Runner test1 { "", statement_sequence };
}

TEST(Statement_Sequence_Tests, single) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	stmt::Statement_Sequence statement_sequence;
	Statement_Sequence_Runner test1 { "a := 3", statement_sequence };
	context::clear();
}

TEST(Statement_Sequence_Tests, multiple) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("b", std::make_shared<expr::Variable>(nullptr));
	stmt::Statement_Sequence statement_sequence;
	Statement_Sequence_Runner test1 { "a := 3;", statement_sequence };
	Statement_Sequence_Runner test2 { "a := 3; b := 4", statement_sequence };
	Statement_Sequence_Runner test3 { "a := 3; b := 4;", statement_sequence };
	context::clear();
}