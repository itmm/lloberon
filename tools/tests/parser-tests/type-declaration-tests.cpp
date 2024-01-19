#include "parser-tests.h"

using Type_Declaration_Runner = Parser_String_Runner<
	&Parser::parse_type_declaration
>;

TEST(Type_Declaration_Tests, empty) {
	context::clear();
	Type_Declaration_Runner test1 { "", true };
}

TEST(Type_Declaration_Tests, simple) {
	context::clear();
	context::scope->register_base_types();
	Type_Declaration_Runner test1 { "a* = INTEGER" };
	auto got { std::dynamic_pointer_cast<type::Type>(context::scope->lookup("a")) };
	EXPECT_NE(got, nullptr);
	if (got) {
		EXPECT_TRUE(got->exported);
		EXPECT_EQ(got, type::Type::base_integer);
	}
}

TEST(Type_Declaration_Tests, incomplete) {
	context::clear();
	Type_Declaration_Runner test1 { "a =", true };

	context::scope->clear();
	Type_Declaration_Runner test2 { "a", true };
}