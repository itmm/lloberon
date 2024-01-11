#include "parser-tests.h"
#include "decl/type.h"
#include "type/base.h"

using Formal_Parameters_Runner = Parser_Value_Runner<
	sema::Formal_Parameters, &Parser::parse_formal_parameters
>;

TEST(Formal_Parameters_Tests, empty) {
	Scope scope;
	sema::Formal_Parameters formal_parameters { scope };
	Formal_Parameters_Runner("", formal_parameters, true);
}

TEST(Formal_Parameters_Tests, simple) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Formal_Parameters formal_parameters { scope };
	Formal_Parameters_Runner test1 { "()", formal_parameters };

	formal_parameters.clear();
	Formal_Parameters_Runner test2 { "(VAR a: BYTE)", formal_parameters };
}

TEST(Formal_Parameters_Tests, with_return) {
	Scope scope;
	auto module = std::make_shared<decl::Module>("X");
	module->insert("Byte", std::make_shared<decl::Type>(type::Base::base_byte));
	scope.insert("X", module);
	sema::Formal_Parameters formal_parameters { scope };
	Formal_Parameters_Runner test1 { "(): X.Byte", formal_parameters };
}

TEST(Formal_Parameters_Tests, incomplete) {
	Scope scope;
	sema::Formal_Parameters formal_parameters { scope };
	Formal_Parameters_Runner test1 { "(", formal_parameters, true };

	formal_parameters.clear();
	Formal_Parameters_Runner test2 { "():", formal_parameters, true };
}