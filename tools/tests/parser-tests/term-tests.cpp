#include "parser-tests.h"
#include "decl/variable.h"

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

TEST(Term_Tests, constant) {
	Scope scope;
	sema::Expression term { scope };
	Term_Runner test1 { "3 * 5", term };
	auto value { std::dynamic_pointer_cast<expr::Const>(term.expression)};
	EXPECT_NE(value, nullptr);
	if (value) {
		EXPECT_TRUE(value->is_int());
		if (value->is_int()) {
			EXPECT_EQ(value->int_value(), 15);
		}
	}

	term.clear();
	Term_Runner  test2 { "15 / 6", term };
	value = std::dynamic_pointer_cast<expr::Const>(term.expression);
	EXPECT_NE(value, nullptr);
	if (value) {
		EXPECT_TRUE(value->is_real());
		if (value->is_real()) {
			EXPECT_EQ(value->real_value(), 2.5);
		}
	}

	term.clear();
	Term_Runner test3 { "15 DIV 6", term };
	value = std::dynamic_pointer_cast<expr::Const>(term.expression);
	EXPECT_NE(value, nullptr);
	if (value) {
		EXPECT_TRUE(value->is_int());
		if (value->is_int()) {
			EXPECT_EQ(value->int_value(), 2);
		}
	}

	term.clear();
	Term_Runner test4 { "15 MOD 6", term };
	value = std::dynamic_pointer_cast<expr::Const>(term.expression);
	EXPECT_NE(value, nullptr);
	if (value) {
		EXPECT_TRUE(value->is_int());
		if (value->is_int()) {
			EXPECT_EQ(value->int_value(), 3);
		}
	}
}