#include "parser-tests.h"
#include "decl/variable.h"
#include "const-tests.h"

using Term_Runner = Parser_Value_Runner<sema::Expression, &Parser::parse_term>;

TEST(Term_Tests, empty) {
	Scope scope;
	sema::Expression term { scope };
	Term_Runner test1 { "", term, true };
}

TEST(Term_Tests, single) {
	Scope scope;
	sema::Expression term { scope };
	Term_Runner test1 { "3", term };
}

TEST(Term_Tests, simple) {
	Scope scope;
	scope.insert("a", std::make_shared<decl::Variable>(nullptr));
	scope.insert("b", std::make_shared<decl::Variable>(nullptr));
	sema::Expression term { scope };
	Term_Runner test1 { "a * b", term };

	term.clear();
	Term_Runner test2 { "a / b", term };

	term.clear();
	Term_Runner test3 { "a DIV b", term };

	term.clear();
	Term_Runner test4 { "a MOD b", term };

	term.clear();
	Term_Runner test5 { "a & b", term };
}

TEST(Term_Tests, multiple) {
	Scope scope;
	scope.insert("a", std::make_shared<decl::Variable>(nullptr));
	scope.insert("b", std::make_shared<decl::Variable>(nullptr));
	scope.insert("c", std::make_shared<decl::Variable>(nullptr));
	sema::Expression term { scope };
	Term_Runner test1 { "a * b * c", term };

	term.clear();
	Term_Runner test2 { "a / 2 DIV b", term };
}

TEST(Term_Tests, incomplete) {
	Scope scope;
	scope.insert("a", std::make_shared<decl::Variable>(nullptr));
	sema::Expression term { scope };
	Term_Runner test1 { "a / 2 DIV", term, true };

	term.clear();
	Term_Runner test2 { "a /", term, true };
}

TEST(Term_Tests, constant_int) {
	Scope scope;
	sema::Expression term { scope };
	Term_Runner test1 { "3 * 5", term };
	expect_int_value(term.expression, 15);

	term.clear();
	Term_Runner  test2 { "15 / 6", term };
	expect_real_value(term.expression, 2.5);

	term.clear();
	Term_Runner test3 { "15 DIV 6", term };
	expect_int_value(term.expression, 2);

	term.clear();
	Term_Runner test4 { "15 MOD 6", term };
	expect_int_value(term.expression, 3);
}

TEST(Term_Tests, constant_real) {
	Scope scope;
	sema::Expression term { scope };
	Term_Runner test1 { "3 * 5.0", term };
	expect_real_value(term.expression, 15.0);

	term.clear();
	Term_Runner  test2 { "15.0 / 6", term };
	expect_real_value(term.expression, 2.5);
}

TEST(Term_Tests, constant_bool) {
	Scope scope;
	sema::Expression term { scope };
	Term_Runner test1 { "FALSE & FALSE", term };
	expect_bool_value(term.expression, false);

	term.clear();
	Term_Runner  test2 { "FALSE & TRUE", term };
	expect_bool_value(term.expression, false);

	term.clear();
	Term_Runner  test3 { "TRUE & FALSE", term };
	expect_bool_value(term.expression, false);

	term.clear();
	Term_Runner  test4 { "TRUE & TRUE", term };
	expect_bool_value(term.expression, true);
}