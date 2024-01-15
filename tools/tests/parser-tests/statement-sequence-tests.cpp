#include "parser-tests.h"
#include "decl/variable.h"

using Statement_Sequence_Runner = Parser_Value_Runner<
	sema::Statement_Sequence, &Parser::parse_statement_sequence
>;

TEST(Statement_Sequence_Tests, empty) {
	Context context;
	sema::Statement_Sequence statement_sequence { context };
	Statement_Sequence_Runner test1 { "", statement_sequence };
}

TEST(Statement_Sequence_Tests, single) {
	Context context;
	context.scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	sema::Statement_Sequence statement_sequence { context };
	Statement_Sequence_Runner test1 { "a := 3", statement_sequence };
}

TEST(Statement_Sequence_Tests, multiple) {
	Context context;
	context.scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	context.scope->insert("b", std::make_shared<decl::Variable>(nullptr));
	sema::Statement_Sequence statement_sequence { context };
	Statement_Sequence_Runner test1 { "a := 3;", statement_sequence };
	Statement_Sequence_Runner test2 { "a := 3; b := 4", statement_sequence };
	Statement_Sequence_Runner test3 { "a := 3; b := 4;", statement_sequence };
}