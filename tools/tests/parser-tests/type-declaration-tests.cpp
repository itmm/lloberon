#include "parser-tests.h"
#include "decl/type.h"

using Type_Declaration_Runner = Parser_Value_Runner<
	Scope, &Parser::parse_type_declaration
>;

TEST(Type_Declaration_Tests, empty) {
	Scope scope;
	Type_Declaration_Runner test1 { "", scope, true };
}

TEST(Type_Declaration_Tests, simple) {
	Scope scope;
	decl::Type::register_base_types(scope);
	Type_Declaration_Runner test1 { "a* = INTEGER", scope };
	auto got { std::dynamic_pointer_cast<decl::Type>(scope.lookup("a")) };
	EXPECT_NE(got, nullptr);
	if (got) {
		EXPECT_TRUE(got->exported);
		EXPECT_EQ(got->type, type::Type::base_integer);
	}
}

TEST(Type_Declaration_Tests, incomplete) {
	Scope scope;
	Type_Declaration_Runner test1 { "a =", scope, true };

	scope.clear();
	Type_Declaration_Runner test2 { "a", scope, true };
}