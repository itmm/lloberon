#include "parser-tests.h"
#include "decl/variable.h"

using Repeat_Statement_Runner = Parser_Value_Runner<
	sema::Repeat_Statement, &Parser::parse_repeat_statement
>;

TEST(Repeat_Statement_Tests, empty) {
	Scope scope;
	sema::Repeat_Statement repeat_statement { scope };
	Repeat_Statement_Runner test1 { "", repeat_statement, true };
}

TEST(Repeat_Statement_Tests, simple) {
	Scope scope;
	scope.insert("a", std::make_shared<decl::Variable>(nullptr));
	sema::Repeat_Statement repeat_statement { scope };
	Repeat_Statement_Runner test1 {
		"REPEAT a := a + 1 UNTIL a > 10", repeat_statement
	};
}