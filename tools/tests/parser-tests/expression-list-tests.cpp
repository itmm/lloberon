#include "parser-tests.h"
#include "decl/variable.h"
#include "decl/procedure.h"

using Expression_List_Runner = Parser_Value_Runner<
	sema::Expression_List, &Parser::parse_expression_list
>;

TEST(Expression_List_Tests, empty) {
	Scope scope;
	sema::Expression_List expression_list { scope };
	Expression_List_Runner test1 { "", expression_list, true };
}

TEST(Expression_List_Tests, single) {
	Scope scope;
	sema::Expression_List expression_list { scope };
	Expression_List_Runner test1 { "3", expression_list };
}

TEST(Expression_List_Tests, multiple) {
	Scope scope;
	scope.insert("f", std::make_shared<decl::Procedure>());
	sema::Expression_List expression_list { scope };
	Expression_List_Runner test1 { "f(3, 4), 4", expression_list };
}

TEST(Expression_List_Tests, incomplete) {
	Scope scope;
	sema::Expression_List expression_list { scope };
	Expression_List_Runner test1 { ",", expression_list, true, true };
	Expression_List_Runner test2 { "3,", expression_list, true };
}