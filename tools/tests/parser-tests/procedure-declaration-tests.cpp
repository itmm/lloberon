#include "parser-tests.h"
#include "decl/variable.h"
#include "decl/type.h"

using Procedure_Declaration_Runner = Parser_Value_Runner<
	Scope, &Parser::parse_procedure_declaration
>;

TEST(Procedure_Declaration_Tests, empty) {
	Scope scope;
	Procedure_Declaration_Runner test1 { "", scope, true };
}

TEST(Procedure_Declaration_Tests, simple) {
	Scope scope;
	decl::Type::register_base_types(scope);
	scope.insert("x", std::make_shared<decl::Variable>(nullptr));
	Procedure_Declaration_Runner test1 {
		"PROCEDURE Add1(x: INTEGER): INTEGER; RETURN x + 1 END Add1", scope
	};
	auto declaration { std::dynamic_pointer_cast<decl::Procedure>(
		scope.lookup("Add1")
	) };
	EXPECT_NE(declaration, nullptr);
	if (declaration) {
		const auto& type { declaration->type };
		EXPECT_EQ(type->return_type, type::Type::base_integer);
		EXPECT_EQ(type->parameters.size(), 1);
		if (!type->parameters.empty()) {
			const auto& first { type->parameters[0] };
			EXPECT_STREQ(first.name.c_str(), "x");
			EXPECT_FALSE(first.reference);
			EXPECT_EQ(first.type, type::Type::base_integer);
		}
	}
}

TEST(Procedure_Declaration_Tests, incomplete) {
	Scope parent;
	Scope scope { &parent };
	decl::Type::register_base_types(parent);
	Procedure_Declaration_Runner test1 {
		"PROCEDURE RETURN", scope, true, true
	};

	scope.clear();
	Procedure_Declaration_Runner test2 {
		"PROCEDURE Answer(): INTEGER; RETURN", scope, true
	};
}