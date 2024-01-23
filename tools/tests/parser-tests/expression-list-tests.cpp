#include "parser-tests.h"
#include "decl/procedure.h"

using Expression_List_Runner = Parser_No_Void_Runner<
	expr::Expression_List, &Parser::parse_expression_list
>;

TEST(Expression_List_Tests, empty) {
	Expression_List_Runner test1 { "", true };
}

TEST(Expression_List_Tests, single) {
	expr::Expression_List expression_list;
	Expression_List_Runner test1 { "3" };
}

TEST(Expression_List_Tests, multiple) {
	context::scope->insert("f", std::make_shared<decl::Procedure>());
	expr::Expression_List expression_list;
	Expression_List_Runner test1 { "f(3, 4), 4" };
	context::clear();
}

TEST(Expression_List_Tests, incomplete) {
	expr::Expression_List expression_list;
	Expression_List_Runner test1 { ",", true, true };
	Expression_List_Runner test2 { "3,", true };
}