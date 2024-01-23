#include "parser-tests.h"
#include "type/type.h"
#include "decl/module.h"

using Qual_Ident_Runner = Parser_No_Void_Runner<
	decl::Declaration_Ptr, &Parser::parse_qual_ident
>;

TEST(Qual_Ident_Tests, empty) {
	Qual_Ident_Runner test1 { "", true };
}

TEST(Qual_Ident_Tests, simple) {
	context::scope->register_base_types();
	Qual_Ident_Runner test1 { "INTEGER" };
	EXPECT_EQ(test1.value, type::Type::base_integer);
	context::scope->clear();

	auto module = std::make_shared<decl::Module>("X");
	context::scope->insert("X", module);
	module->insert("Byte", type::Type::base_byte);
	Qual_Ident_Runner test2 { "X.Byte" };
	EXPECT_EQ(test2.value, type::Type::base_byte);
	context::clear();
}

TEST(Qual_Ident_Tests, incomplete) {
	auto module = std::make_shared<decl::Module>("X");
	context::scope->insert("X", module);
	Qual_Ident_Runner test1 { "X.", true };
	Qual_Ident_Runner test2 { ".", true, true };
	context::clear();
}