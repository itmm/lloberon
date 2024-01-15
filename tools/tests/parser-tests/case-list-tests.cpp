#include "parser-tests.h"

using Const_Case_List_Runner = Parser_Value_Runner<
	sema::Const_Case_List, &Parser::parse_case_list
>;

TEST(Const_Case_List_Tests, empty) {
	Context context;
	sema::Const_Case_List case_list { context };
	Const_Case_List_Runner test1 { "", case_list, true };
}

TEST(Const_Case_List_Tests, single) {
	Context context;
	sema::Const_Case_List case_list { context };
	Const_Case_List_Runner test1 { "3..4", case_list };
}

TEST(Case_List_Tests, multiple) {
	Context context;
	sema::Const_Case_List case_list { context };
	Const_Case_List_Runner test1 { "3..4, 7..8, 12", case_list };
}

TEST(Case_List_Tests, incomplete) {
	Context context;
	sema::Const_Case_List case_list { context };
	Const_Case_List_Runner test1 { "3,", case_list, true };
}