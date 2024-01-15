#include "parser-tests.h"
#include "decl/type.h"

using Type_Declaration_Runner = Parser_Value_Runner<
	Context, &Parser::parse_type_declaration
>;

TEST(Type_Declaration_Tests, empty) {
	Context context;
	Type_Declaration_Runner test1 { "", context, true };
}

TEST(Type_Declaration_Tests, simple) {
	Context context;
	decl::Type::register_base_types(*context.scope);
	Type_Declaration_Runner test1 { "a* = INTEGER", context };
	auto got { std::dynamic_pointer_cast<decl::Type>(context.scope->lookup("a")) };
	EXPECT_NE(got, nullptr);
	if (got) {
		EXPECT_TRUE(got->exported);
		EXPECT_EQ(got->type, type::Type::base_integer);
	}
}

TEST(Type_Declaration_Tests, incomplete) {
	Context context;
	Type_Declaration_Runner test1 { "a =", context, true };

	context.scope->clear();
	Type_Declaration_Runner test2 { "a", context, true };
}