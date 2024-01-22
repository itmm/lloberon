#include "parser-tests.h"

using Const_Case_List_Runner = Parser_Arg_Void_Runner<
	sema::Const_Case_List, &Parser::parse_case_list
>;

using Type_Case_List_Runner = Parser_Arg_Void_Runner<
	sema::Type_Case_List, &Parser::parse_case_list
>;

TEST(Const_Case_List_Tests, empty) {
	sema::Const_Case_List case_list;
	Const_Case_List_Runner test1 { "", case_list, true };
}

TEST(Const_Case_List_Tests, single) {
	sema::Const_Case_List case_list;
	Const_Case_List_Runner test1 { "3..4", case_list };
}

TEST(Case_List_Tests, multiple) {
	sema::Const_Case_List const_cases;
	Const_Case_List_Runner test1 { "3..4, 7..8, 12", const_cases};
	EXPECT_EQ(const_cases.size(), 3);

	context::scope->register_base_types();
	sema::Type_Case_List type_cases;
	Type_Case_List_Runner test2 { "INTEGER, BYTE", type_cases};
	EXPECT_EQ(type_cases.size(), 2);
	context::clear();
}

TEST(Case_List_Tests, incomplete) {
	sema::Const_Case_List case_list;
	Const_Case_List_Runner test1 { "3,", case_list, true };
}