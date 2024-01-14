#include "decl/type.h"
#include "parser-tests.h"
#include "type/type.h"

using Formal_Parameters_Runner = Parser_Value_Runner<
	sema::Procedure_Type, &Parser::parse_formal_parameters
>;

TEST(Formal_Parameters_Tests, empty) {
	Scope scope;
	sema::Procedure_Type procedure_type { scope };
	Formal_Parameters_Runner("", procedure_type, true);
}

TEST(Formal_Parameters_Tests, simple) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Procedure_Type procedure_type { scope };
	Formal_Parameters_Runner test1 { "()", procedure_type };
	EXPECT_TRUE(procedure_type.procedure->parameters.empty());
	EXPECT_EQ(procedure_type.procedure->return_type, nullptr);

	Formal_Parameters_Runner test2 { "(VAR a: BYTE)", procedure_type };
	EXPECT_EQ(procedure_type.procedure->parameters.size(), 1);
	if (!procedure_type.procedure->parameters.empty()) {
		const auto& first { procedure_type.procedure->parameters[0] };
		EXPECT_STREQ(first.name.c_str(), "a");
		EXPECT_EQ(first.type, type::Type::base_byte);
		EXPECT_TRUE(first.reference);
	}
	EXPECT_EQ(procedure_type.procedure->return_type, nullptr);
}

TEST(Formal_Parameters_Tests, with_return) {
	Scope scope;
	auto module = std::make_shared<decl::Module>("X");
	module->insert("Byte", std::make_shared<decl::Type>(type::Type::base_byte));
	scope.insert("X", module);
	sema::Procedure_Type procedure_type { scope };
	Formal_Parameters_Runner test1 { "(): X.Byte", procedure_type };
	EXPECT_EQ(procedure_type.procedure->parameters.size(), 0);
	const auto& return_type { procedure_type.procedure->return_type };
	EXPECT_EQ(return_type, type::Type::base_byte);
}

TEST(Formal_Parameters_Tests, incomplete) {
	Scope scope;
	sema::Procedure_Type procedure_type { scope };
	Formal_Parameters_Runner test1 { "(", procedure_type, true };
	Formal_Parameters_Runner test2 { "():", procedure_type, true };
}