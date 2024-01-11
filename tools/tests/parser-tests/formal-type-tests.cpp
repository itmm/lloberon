#include "decl/type.h"
#include "parser-tests.h"
#include "type/array.h"

using Formal_Type_Runner = Parser_Value_Runner<
	sema::Type, &Parser::parse_formal_type
>;

TEST(Formal_Type_Tests, empty) {
	Scope scope;
	sema::Type formal_type { scope };
	Formal_Type_Runner test1 { "", formal_type, true };
}

TEST(Formal_Type_Tests, simple) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Type formal_type { scope };
	Formal_Type_Runner test1 { "INTEGER", formal_type };
	EXPECT_EQ(formal_type.type, type::Type::base_integer);
}

TEST(Formal_Type_Tests, qualified) {
	Scope scope;
	auto module { std::make_shared<decl::Module>("X") };
	module->insert("Byte", std::make_shared<decl::Type>(
		type::Type::base_byte
	));
	scope.insert("X", module);
	sema::Type formal_type { scope };
	Formal_Type_Runner test1 { "X.Byte", formal_type };
	EXPECT_EQ(formal_type.type, type::Type::base_byte);
}

TEST(Formal_Type_Tests, array) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Type formal_type { scope };
	Formal_Type_Runner test1 { "ARRAY OF BYTE", formal_type };
	auto array { std::dynamic_pointer_cast<type::Array>(formal_type.type) };
	EXPECT_NE(array, nullptr);
	if (array) {
		EXPECT_EQ(array->count, -1);
		EXPECT_EQ(array->base, type::Type::base_byte);
	}
}

TEST(Formal_Type_Tests, multiple_arrays) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Type formal_type { scope };
	Formal_Type_Runner test1 { "ARRAY OF ARRAY OF BYTE", formal_type };
	auto outer { std::dynamic_pointer_cast<type::Array>(formal_type.type) };
	EXPECT_NE(outer, nullptr);
	if (outer) {
		EXPECT_EQ(outer->count, -1);
		auto inner { std::dynamic_pointer_cast<type::Array>(outer->base) };
		EXPECT_NE(inner, nullptr);
		if (inner) {
			EXPECT_EQ(outer->count, -1);
			EXPECT_EQ(inner->base, type::Type::base_byte);
		}
	}
}