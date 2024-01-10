#include "parser-tests.h"
#include "decl/type.h"
#include "type/base.h"

using Formal_Type_Runner = Parser_Value_Runner<
	sema::Formal_Type, &Parser::parse_formal_type
>;

TEST(Formal_Type_Tests, empty) {
	Scope scope;
	sema::Formal_Type formal_type { scope };
	Formal_Type_Runner test1 { "", formal_type, true };
}

TEST(Formal_Type_Tests, simple) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Formal_Type formal_type { scope };
	Formal_Type_Runner test1 { "INTEGER", formal_type };
}

TEST(Formal_Type_Tests, qualified) {
	Scope scope;
	auto module { std::make_shared<decl::Module>(
		"X"
	) };
	module->insert("Byte", std::make_shared<decl::Type>(
		std::make_shared<type::Base>(type::Base::bt_BYTE)
	));
	scope.insert("X", module);
	sema::Formal_Type formal_type { scope };
	Formal_Type_Runner test1 { "X.Byte", formal_type };
}

TEST(Formal_Type_Tests, array) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Formal_Type formal_type { scope };
	Formal_Type_Runner test1 { "ARRAY OF BYTE", formal_type };
}

TEST(Formal_Type_Tests, multiple_arrays) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Formal_Type formal_type { scope };
	Formal_Type_Runner test1 { "ARRAY OF ARRAY OF BYTE", formal_type };
}