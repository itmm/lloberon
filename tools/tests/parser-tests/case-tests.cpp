#include "parser-tests.h"

#include "decl/variable.h"

using Case_Runner = Parser_Value_Runner<sema::Const_Case, &Parser::parse_case>;

TEST(Case_Tests, empty) {
	context::clear();
	sema::Const_Case const_case;
	Case_Runner("", const_case, true);
}

TEST(Case_Tests, simple) {
	context::clear();
	context::scope->insert("a", std::make_shared<decl::Variable>(
		type::Type::base_integer
	));
	sema::Const_Case const_case;
	Case_Runner test1 { "3..4:", const_case };
	Case_Runner test2 { "3..4: a := 3", const_case };
}

TEST(Case_Tests, wrong) {
	context::clear();
	context::scope->insert("a", std::make_shared<decl::Variable>(
		type::Type::base_integer
	));
	sema::Const_Case const_case;
	Case_Runner test1 { "3 a := 3", const_case, true, true };
	Case_Runner test2 { "3", const_case, true };
}