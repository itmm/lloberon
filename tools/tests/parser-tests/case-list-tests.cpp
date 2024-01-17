#include "parser-tests.h"

using Const_Case_List_Runner = Parser_Value_Runner<
	sema::Const_Case_List, &Parser::parse_case_list
>;

TEST(Const_Case_List_Tests, empty) {
	context::clear();
	sema::Const_Case_List case_list;
	Const_Case_List_Runner test1 { "", case_list, true };
}

TEST(Const_Case_List_Tests, single) {
	context::clear();
	sema::Const_Case_List case_list;
	Const_Case_List_Runner test1 { "3..4", case_list };
}

TEST(Case_List_Tests, multiple) {
	context::clear();
	sema::Const_Case_List case_list;
	Const_Case_List_Runner test1 { "3..4, 7..8, 12", case_list };
}

TEST(Case_List_Tests, incomplete) {
	context::clear();
	sema::Const_Case_List case_list;
	Const_Case_List_Runner test1 { "3,", case_list, true };
}