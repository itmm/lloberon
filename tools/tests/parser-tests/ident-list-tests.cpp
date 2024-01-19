#include "parser-tests.h"

#include "ident-list-tests.h"

using Ident_List_Runner = Parser_Value_Runner<
	sema::Ident_List, &Parser::parse_ident_list
>;

TEST(Ident_List_Tests, empty) {
	sema::Ident_List list;
	list.emplace_back("x");
	Ident_List_Runner test1 { "", list, true };
	expect_empty_ident_list(list);
}

TEST(Ident_List_Tests, single) {
	sema::Ident_List list;
	list.emplace_back("x");
	Ident_List_Runner test1 { "abc", list };
	expect_ident_list(list, "abc", false);
	Ident_List_Runner test2 { "abc*", list };
	expect_ident_list(list, "abc", true);
}

TEST(Identlist_Tests, multiple) {
	sema::Ident_List list;
	list.emplace_back("x");
	Ident_List_Runner test1 { "a, b*, c", list };
	expect_ident_list(list, "a", false, "b", true, "c", false);
	Ident_List_Runner test2 { "d*, e, f*", list };
	expect_ident_list(list, "d", true, "e", false, "f", true);
	Ident_List_Runner test3 { "a, b", list };
	expect_ident_list(list, "a", false, "b", false);

	Ident_List_Runner test4 { "c*, d*", list };
	expect_ident_list(list, "c", true, "d", true);
}

TEST(Identlist_Tests, empty_items) {
	sema::Ident_List list;
	list.emplace_back("x");
	Ident_List_Runner test1 { "a,", list, true };

	list.emplace_back("x");
	Ident_List_Runner test2 { ",", list, true, true };

	list.emplace_back("x");
	Ident_List_Runner test3 { "a,,b", list, true, true };

}

TEST(Identlist_Tests, wrong_items) {
	sema::Ident_List list;
	list.emplace_back("x");
	Ident_List_Runner test1 { "1", list, true, true };

	list.emplace_back("x");
	Ident_List_Runner test2 { "a,2", list, true, true };
}