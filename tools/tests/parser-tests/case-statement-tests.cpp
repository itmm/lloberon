#include "parser-tests.h"
#include "decl/variable.h"

using Case_Statement_Runner = Parser_Value_Runner<
	sema::Statement, &Parser::parse_case_statement
>;

TEST(Case_Statetment_Tests, empty) {
	Context context;
	sema::Statement statement { context };
	Case_Statement_Runner("", statement, true);
}

TEST(Case_Statement_Tests, single) {
	Context context;
	context.scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	context.scope->insert("x", std::make_shared<decl::Variable>(nullptr));
	sema::Statement statement { context };
	Case_Statement_Runner test1 { "", statement, true };
	Case_Statement_Runner test2 { "CASE a OF 3: x := 1 END", statement };
}

TEST(Case_Statement_Tests, multiple) {
	Context context;
	context.scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	context.scope->insert("x", std::make_shared<decl::Variable>(nullptr));
	sema::Statement statement { context };
	Case_Statement_Runner test1 {
		"CASE a OF 3: x := 1 | 2, 4: x := 2 END", statement
	};
}

TEST(Case_Statement_Tests, wrong) {
	Context context;
	context.scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	sema::Statement statement { context };
	Case_Statement_Runner test1 { "CASE OF", statement, true, true };
	Case_Statement_Runner test2 { "CASE a 3:", statement, true, true };
	Case_Statement_Runner test3 { "CASE a OF END", statement, true, true };
	Case_Statement_Runner test4 { "CASE a OF 3: |", statement, true };
}