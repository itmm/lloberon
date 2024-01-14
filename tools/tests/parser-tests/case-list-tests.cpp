#include "parser-tests.h"

using Const_Case_List_Runner = Parser_Value_Runner<
	sema::Const_Case_List, &Parser::parse_case_list
>;

TEST(Const_Case_List_Tests, empty) {
	Scope scope;
	sema::Const_Case_List case_list { scope };
	Const_Case_List_Runner test1 { "", case_list, true };
}

TEST(Const_Case_List_Tests, single) {
	Scope scope;
	sema::Const_Case_List case_list { scope };
	Const_Case_List_Runner test1 { "3..4", case_list };
}

TEST(Case_List_Tests, multiple) {
	Scope scope;
	sema::Const_Case_List case_list { scope };
	Const_Case_List_Runner test1 { "3..4, 7..8, 12", case_list };
}

TEST(Case_List_Tests, incomplete) {
	Scope scope;
	sema::Const_Case_List case_list { scope };
	Const_Case_List_Runner test1 { "3,", case_list, true };
}