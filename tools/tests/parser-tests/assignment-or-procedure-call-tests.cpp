#include "parser-tests.h"

#include "decl/variable.h"
#include "decl/type.h"
#include "decl/procedure.h"

using Assignment_Runner = Parser_Value_Runner<
	expr::Expression_Ptr, &Parser::parse_assignment_or_procedure_call
>;
using Procedure_Call_Runner = Assignment_Runner;

TEST(Assignment_Tests, empty) {
	context::clear();
	expr::Expression_Ptr assignment;
	Assignment_Runner("", assignment, true);
}

TEST(Assignment_Tests, simple) {
	context::clear();
	context::scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	expr::Expression_Ptr assignment;
	Assignment_Runner("a := 3", assignment);
}

TEST(Assignment_Tests, incomplete) {
	context::clear();
	context::scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	expr::Expression_Ptr assignment;
	Assignment_Runner("a :=", assignment, true);
}

TEST(Procedure_Call_Tests, simple) {
	context::clear();
	context::scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	context::scope->insert("f", std::make_shared<decl::Procedure>());
	expr::Expression_Ptr assignment;
	Procedure_Call_Runner test1 { "f()", assignment };

	Procedure_Call_Runner test2 { "f(a, 3)", assignment };
}

TEST(Procedure_Call_Tests, odd) {
	context::clear();
	decl::Procedure::register_base_procedures(*context::scope);
	expr::Expression_Ptr assignment;
	Procedure_Call_Runner test1 { "ODD(4)", assignment };
}

TEST(Procedure_Call_Tests, incomplete) {
	context::clear();
	context::scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	context::scope->insert("f", std::make_shared<decl::Procedure>());
	expr::Expression_Ptr assignment;
	Procedure_Call_Runner test1 { "f(a,", assignment, true };
	Procedure_Call_Runner test2 { "f(a", assignment, true };
	Procedure_Call_Runner test3 { "f(", assignment, true };
}

TEST(Procedure_Call_Tests, cast) {
	context::clear();
	decl::Type::register_base_types(*context::scope);
	context::scope->insert("a", std::make_shared<decl::Variable>(nullptr));
	expr::Expression_Ptr assignment;
	Procedure_Call_Runner test1 { "a (INTEGER)", assignment };
}
