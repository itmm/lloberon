#include "ident-def-tests.h"
#include "parser-tests.h"

using Ident_Def_Runner = Parser_No_Void_Runner<
	sema::Ident_Def, &Parser::parse_ident_def
>;

TEST(IDent_Def_Tests, empty) {
	Ident_Def_Runner test1 { "", true };
}

TEST(Ident_Def_Tests, simple_ident) {
	Ident_Def_Runner test1 { "abc" };
	expect_ident_def(test1.value, "abc", false);
}

TEST(Ident_Def_Tests, exported_ident) {
	Ident_Def_Runner test1 { "abc*" };
	expect_ident_def(test1.value, "abc", true);
}

TEST(Ident_Def_Tests, empty_isnt_ident) {
	Ident_Def_Runner test1 { "", true };
}

TEST(Ident_Def_Tests, number_isnt_ident) {
	Ident_Def_Runner test1 { "123", true, true };
}

TEST(Ident_Def_Tests, star_isnt_ident) {
	Ident_Def_Runner test1 { "*", true, true };
}