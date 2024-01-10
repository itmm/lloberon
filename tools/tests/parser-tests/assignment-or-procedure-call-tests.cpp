#include "parser-tests.h"

#include "decl/variable.h"
#include "decl/type.h"

using Assignment_Runner = Parser_Value_Runner<
	sema::Assignment_Or_Procedure_Call,
	&Parser::parse_assignment_or_procedure_call
>;
using Procedure_Call_Runner = Assignment_Runner;

TEST(Assignment_Tests, empty) {
	Scope scope;
	sema::Assignment_Or_Procedure_Call assignment { scope };
	Assignment_Runner("", assignment, true);
}

TEST(Assignment_Tests, simple) {
	Scope scope;
	scope.insert("a", std::make_shared<decl::Variable>(
		nullptr
	));
	sema::Assignment_Or_Procedure_Call assignment { scope };
	Assignment_Runner("a := 3", assignment);
}

TEST(Assignment_Tests, incomplete) {
	Scope scope;
	scope.insert("a", std::make_shared<decl::Variable>(
		nullptr
	));
	sema::Assignment_Or_Procedure_Call assignment { scope };
	Assignment_Runner("a :=", assignment, true);
}

TEST(Procedure_Call_Tests, simple) {
	Scope scope;
	scope.insert("a", std::make_shared<decl::Variable>(
		nullptr
	));
	scope.insert("f", std::make_shared<decl::Variable>(
		nullptr
	));
	sema::Assignment_Or_Procedure_Call assignment { scope };
	Procedure_Call_Runner test1 { "f()", assignment };

	assignment.clear();
	Procedure_Call_Runner test2 { "f(a, 3)", assignment };
}

TEST(Procedure_Call_Tests, incomplete) {
	Scope scope;
	scope.insert("a", std::make_shared<decl::Variable>(
		nullptr
	));
	scope.insert("f", std::make_shared<decl::Variable>(
		nullptr
	));
	sema::Assignment_Or_Procedure_Call assignment { scope };
	Procedure_Call_Runner test1 { "f(a,", assignment, true };

	assignment.clear();
	Procedure_Call_Runner test2 { "f(a", assignment, true };

	assignment.clear();
	Procedure_Call_Runner test3 { "f(", assignment, true };
}

TEST(Procedure_Call_Tests, cast) {
	Scope scope;
	decl::Type::register_base_types(scope);
	scope.insert("a", std::make_shared<decl::Variable>(
		nullptr
	));
	sema::Assignment_Or_Procedure_Call assignment { scope };
	Procedure_Call_Runner test1 { "a (INTEGER)", assignment };
}
