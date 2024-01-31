#include "parser-tests.h"

#include "ident-list-tests.h"

using Ident_List_Runner = Parser_No_Void_Runner<
	sema::Ident_List, &Parser::parse_ident_list
>;

TEST(Ident_List_Tests, empty) {
	Ident_List_Runner test1 { "", true };
	expect_empty_ident_list(test1.value);
}

TEST(Ident_List_Tests, single) {
	Ident_List_Runner test1 { "abc" };
	expect_ident_list(test1.value, "abc", false);
	Ident_List_Runner test2 { "abc*" };
	expect_ident_list(test2.value, "abc", true);
}

TEST(Identlist_Tests, multiple) {
	Ident_List_Runner test1 { "a, b*, c" };
	expect_ident_list(test1.value, "a", false, "b", true, "c", false);
	Ident_List_Runner test2 { "d*, e, f*" };
	expect_ident_list(test2.value, "d", true, "e", false, "f", true);
	Ident_List_Runner test3 { "a, b" };
	expect_ident_list(test3.value, "a", false, "b", false);

	Ident_List_Runner test4 { "c*, d*" };
	expect_ident_list(test4.value, "c", true, "d", true);
}

TEST(Identlist_Tests, empty_items) {
	Ident_List_Runner test1 { "a,", true };
	Ident_List_Runner test2 { ",", true, true };
	Ident_List_Runner test3 { "a,,b", true, true };
}

TEST(Identlist_Tests, wrong_items) {
	Ident_List_Runner test1 { "1", true, true };
	Ident_List_Runner test2 { "a,2", true, true };
}