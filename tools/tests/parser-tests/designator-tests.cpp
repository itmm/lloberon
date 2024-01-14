#include "parser-tests.h"
#include "decl/variable.h"

using Designator_Runner = Parser_Value_Runner<
	sema::Designator, &Parser::parse_designator
>;

TEST(Designator_Tests, empty) {
	Scope scope;
	sema::Designator designator { scope };
	Designator_Runner test1 { "", designator, true };
}

TEST(Designator_Tests, simple) {
	Scope scope;
	scope.insert("a", std::make_shared<decl::Variable>(nullptr));
	sema::Designator designator { scope };
	Designator_Runner test1 { "a", designator };
	Designator_Runner test2 { "a.b", designator };
	Designator_Runner test3 { "a.b.c", designator };
	Designator_Runner test4 { "a.b[2, 3]", designator };
	Designator_Runner test5 { "a.b^", designator };
}

TEST(Designator_Tests, combined) {
	Scope scope;
	sema::Designator designator { scope };
	scope.insert("a", std::make_shared<decl::Variable>(nullptr));
	Designator_Runner test1 { "a.b^[3].c^", designator };
}

TEST(Designator_Tests, incomplete) {
	Scope scope;
	sema::Designator designator { scope };
	scope.insert("a", std::make_shared<decl::Variable>(nullptr));
	Designator_Runner test1 { "a[3,", designator, true };
	Designator_Runner test2 { "a[3", designator, true };
	Designator_Runner test3 { "a[3,]", designator, true, true };
	Designator_Runner test4 { "a[]", designator, true, true };
	Designator_Runner test5 { "a.b.", designator, true };
	Designator_Runner test6 { "a.b.[", designator, true, true };
	Designator_Runner test7 { "a.b.^", designator, true, true };
	Designator_Runner test8 { "a.", designator, true };
	Designator_Runner test9 { "a.[", designator, true, true };
	Designator_Runner test10 { "a.^", designator, true, true };
}