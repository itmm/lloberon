#include "parser-tests.h"

#include "decl/procedure.h"
#include "expr/variable.h"

using Assignment_Runner = Parser_Arg_Void_Runner<
	expr::Expression_Ptr, &Parser::parse_assignment_or_procedure_call
>;
using Procedure_Call_Runner = Assignment_Runner;

TEST(Assignment_Tests, empty) {
	expr::Expression_Ptr assignment;
	Assignment_Runner test1 { "", assignment, true };
}

TEST(Assignment_Tests, simple) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	expr::Expression_Ptr assignment;
	Assignment_Runner test1 { "a := 3", assignment };
	context::clear();
}

TEST(Assignment_Tests, incomplete) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	expr::Expression_Ptr assignment;
	Assignment_Runner test1 { "a :=", assignment, true };
	context::clear();
}

TEST(Procedure_Call_Tests, simple) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("f", std::make_shared<decl::Procedure>());
	expr::Expression_Ptr assignment;
	Procedure_Call_Runner test1 { "f()", assignment };

	Procedure_Call_Runner test2 { "f(a, 3)", assignment };
	context::clear();
}

TEST(Procedure_Call_Tests, odd) {
	decl::Procedure::register_base_procedures(*context::scope);
	expr::Expression_Ptr assignment;
	Procedure_Call_Runner test1 { "ODD(4)", assignment };
	context::clear();
}

TEST(Procedure_Call_Tests, incomplete) {
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	context::scope->insert("f", std::make_shared<decl::Procedure>());
	expr::Expression_Ptr assignment;
	Procedure_Call_Runner test1 { "f(a,", assignment, true };
	Procedure_Call_Runner test2 { "f(a", assignment, true };
	Procedure_Call_Runner test3 { "f(", assignment, true };
	context::clear();
}

TEST(Procedure_Call_Tests, cast) {
	context::scope->register_base_types();
	context::scope->insert("a", std::make_shared<expr::Variable>(nullptr));
	expr::Expression_Ptr assignment;
	Procedure_Call_Runner test1 { "a (INTEGER)", assignment };
	context::clear();
}
