#include "parser-tests.h"
#include "decl/variable.h"
#include "expr/const.h"
#include "const-tests.h"
#include "type-tests.h"

using Factor_Runner = Parser_Value_Runner<
	expr::Expression_Ptr, &Parser::parse_factor
>;

TEST(Factor_Tests, empty) {
	context::clear();
	expr::Expression_Ptr factor;
	Factor_Runner("", factor, true);
}

TEST(Factor_Tests, literals) {
	context::clear();
	expr::Expression_Ptr factor;
	Factor_Runner test1 { "3", factor };
	expect_int_value(factor, 3);

	Factor_Runner test2 { "3.241", factor };
	expect_real_value(factor, 3.241);

	Factor_Runner test3 { "\"abc\"", factor };
	expect_string_value(factor, "abc");

	Factor_Runner test4 { "020H", factor };
	expect_int_value(factor, 32);

	Factor_Runner test5 { "40X", factor };
	expect_string_value(factor, "@");

	Factor_Runner test6 { "NIL", factor };
	EXPECT_EQ(factor, expr::Expression::nil);

	Factor_Runner test7 { "TRUE", factor };
	expect_bool_value(factor, true);

	Factor_Runner test8 { "FALSE", factor };
	expect_bool_value(factor, false);
}

TEST(Factor_Tests, set) {
	context::clear();
	expr::Expression_Ptr factor;
	Factor_Runner test1 { "{3..5}", factor };
}

TEST(Factor_Tests, grouped) {
	context::clear();
	expr::Expression_Ptr factor;
	Factor_Runner test1 { "(3 + 4)", factor };
	expect_int_value(factor, 7);
}

TEST(Factor_Tests, ident) {
	context::clear();
	auto base { std::make_shared<Scope>() };
	decl::Type::register_base_types(*base);
	context::scope = std::make_shared<Scope>(base);
	type::Type_Ptr type;
	Type_Runner type_runner { "ARRAY 10 OF PROCEDURE(x: BOOLEAN)", type };
	context::scope->insert("a", std::make_shared<decl::Variable>(type));
	context::scope->insert("f", std::make_shared<decl::Procedure>());
	expr::Expression_Ptr factor;
	Factor_Runner test1 { "a", factor };
	Factor_Runner test2 { "f(3, TRUE)", factor };
	Factor_Runner test3 { "a[3](TRUE)", factor };
}

TEST(Factor_Tests, not) {
	context::clear();
	expr::Expression_Ptr factor;
	Factor_Runner test1 { "~FALSE", factor };
	auto value { expr::Const::as_const(factor) };
	EXPECT_NE(value, nullptr);
	if (value) {
		EXPECT_TRUE(value->is_bool() && value->bool_value());
	}
}

TEST(Factor_Tests, incomplete) {
	context::clear();
	context::scope->insert("a", std::make_shared<decl::Procedure>());
	expr::Expression_Ptr factor;
	Factor_Runner test1 { "a(3,TRUE", factor, true };
	Factor_Runner test2 { "a(3,", factor, true };
	Factor_Runner test3 { "a(3", factor, true };
	Factor_Runner test4 { "a(", factor, true };
}