#include "parser-tests.h"
#include "decl/variable.h"
#include "stmt/for.h"
#include "const-tests.h"

using For_Statement_Runner = Parser_Value_Runner<
	sema::Statement, &Parser::parse_for_statement
>;

TEST(For_Statement_Tests, empty) {
	Scope scope;
	sema::Statement statement { scope };
	For_Statement_Runner test1 { "", statement, true };
}

TEST(For_Statement_Tests, simple) {
	Scope scope;
	auto var { std::make_shared<decl::Variable>(nullptr) };
	scope.insert("a", var);
	scope.insert("x", std::make_shared<decl::Variable>(nullptr));
	sema::Statement statement { scope };
	For_Statement_Runner test1 {
		"FOR a := 1 TO 3 DO x := x + a END", statement
	};
	auto for_statement { std::dynamic_pointer_cast<stmt::For>(
		statement.statement
	)};
	EXPECT_NE(for_statement, nullptr);
	if (for_statement) {
		EXPECT_EQ(for_statement->variable, var);
		expect_int_value(for_statement->begin, 1);
		expect_int_value(for_statement->end, 3);
		expect_int_value(for_statement->increment, 1);
		EXPECT_EQ(for_statement->statements.size(), 1);
	}
}

TEST(For_Statement_Tests, with_step) {
	Scope scope;
	auto var { std::make_shared<decl::Variable>(nullptr) };
	scope.insert("a", var);
	scope.insert("x", std::make_shared<decl::Variable>(nullptr));
	sema::Statement statement { scope };
	For_Statement_Runner test1 {
		"FOR a := 1 TO 10 BY 2 DO x := x + a END", statement
	};
	auto for_statement { std::dynamic_pointer_cast<stmt::For>(
		statement.statement
	)};
	EXPECT_NE(for_statement, nullptr);
	if (for_statement) {
		EXPECT_EQ(for_statement->variable, var);
		expect_int_value(for_statement->begin, 1);
		expect_int_value(for_statement->end, 10);
		expect_int_value(for_statement->increment, 2);
		EXPECT_EQ(for_statement->statements.size(), 1);
	}
}

TEST(For_Statement_Tests, with_stepdown) {
	Scope scope;
	auto var { std::make_shared<decl::Variable>(nullptr) };
	scope.insert("a", var);
	scope.insert("x", std::make_shared<decl::Variable>(nullptr));
	sema::Statement statement { scope };
	For_Statement_Runner test1 {
		"FOR a := 10 TO 0 BY -2 DO x := x + a END", statement
	};
	auto for_statement { std::dynamic_pointer_cast<stmt::For>(
		statement.statement
	)};
	EXPECT_NE(for_statement, nullptr);
	if (for_statement) {
		EXPECT_EQ(for_statement->variable, var);
		expect_int_value(for_statement->begin, 10);
		expect_int_value(for_statement->end, 0);
		expect_int_value(for_statement->increment, -2);
		EXPECT_EQ(for_statement->statements.size(), 1);
	}
}

TEST(For_Statement_Tests, wrong) {
	Scope scope;
	scope.insert("a", std::make_shared<decl::Variable>(nullptr));
	sema::Statement statement { scope };
	For_Statement_Runner test1 { "FOR", statement, true };

	statement.clear();
	For_Statement_Runner test2 { "FOR a", statement, true };

	statement.clear();
	For_Statement_Runner test3 { "FOR :=", statement, true, true };

	statement.clear();
	For_Statement_Runner test4 { "FOR a :=", statement, true };

	statement.clear();
	For_Statement_Runner test5 { "FOR a 1", statement, true, true };

	statement.clear();
	For_Statement_Runner test6 { "FOR a := 1", statement, true };

	statement.clear();
	For_Statement_Runner test7 { "FOR a := 1 TO", statement, true };

	statement.clear();
	For_Statement_Runner test8 { "FOR a := 1 TO 10", statement, true };

	statement.clear();
	For_Statement_Runner test9 { "FOR a := 1 10", statement, true, true };

	statement.clear();
	For_Statement_Runner test10 { "FOR a := 1 TO 10 DO", statement, true };

	statement.clear();
	For_Statement_Runner test11 {
		"FOR a := 1 TO 10 END", statement, true, true
	};

	statement.clear();
	For_Statement_Runner test12 {
		"FOR a := 1 TO 10 BY DO", statement, true, true
	};
}