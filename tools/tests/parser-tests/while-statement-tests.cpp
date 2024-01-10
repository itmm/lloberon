#include "parser-tests.h"
#include "decl/variable.h"

using While_Statement_Runner = Parser_Value_Runner<
	sema::While_Statement, &Parser::parse_while_statement
>;

TEST(While_Statement_Tests, empty) {
	Scope scope;
	sema::While_Statement while_statement { scope };
	While_Statement_Runner test1 { "", while_statement, true };
}

TEST(While_Statement_Tests, simple) {
	Scope scope;
	scope.insert("a", std::make_shared<decl::Variable>(
		nullptr
	));
	scope.insert("INC", std::make_shared<decl::Variable>(
		nullptr
	));
	sema::While_Statement while_statement { scope };
	While_Statement_Runner test1 {
		"WHILE a < 3 DO INC(a) END", while_statement
	};
}

TEST(While_Statement_Tests, with_elsif) {
	Scope scope;
	scope.insert("a", std::make_shared<decl::Variable>(
		nullptr
	));
	scope.insert("b", std::make_shared<decl::Variable>(
		nullptr
	));
	scope.insert("c", std::make_shared<decl::Variable>(
		nullptr
	));
	scope.insert("INC", std::make_shared<decl::Variable>(
		nullptr
	));
	sema::While_Statement while_statement { scope };
	While_Statement_Runner test1 {
		"WHILE a < 3 DO INC(a) ELSIF b < 3 DO INC(b) ELSIF c < 3 DO INC(c) END",
		while_statement
	};
}

TEST(While_Statement_Tests, wrong) {
	Scope scope;
	scope.insert("a", std::make_shared<decl::Variable>(
		nullptr
	));
	scope.insert("INC", std::make_shared<decl::Variable>(
		nullptr
	));
	sema::While_Statement while_statement { scope };
	While_Statement_Runner test1 { "WHILE DO", while_statement, true, true };

	while_statement.clear();
	While_Statement_Runner test2 {
		"WHILE a < 3 DO INC(a)", while_statement, true
	};

	while_statement.clear();
	While_Statement_Runner test3 {
		"WHILE a ELSIF", while_statement, true, true
	};

	while_statement.clear();
	While_Statement_Runner test4 {
		"WHILE a < 3 DO ELSIF END", while_statement, true, true
	};
}