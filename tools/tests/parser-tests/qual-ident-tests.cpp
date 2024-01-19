#include "parser-tests.h"
#include "type/type.h"

using Qual_Ident_Runner = Parser_Value_Runner<
	sema::Qual_Ident, &Parser::parse_qual_ident
>;

TEST(Qual_Ident_Tests, empty) {
	sema::Qual_Ident qual_ident;
	Qual_Ident_Runner test1 { "", qual_ident, true };
}

TEST(Qual_Ident_Tests, simple) {
	context::scope->register_base_types();
	sema::Qual_Ident qual_ident;
	Qual_Ident_Runner test1 { "BYTE", qual_ident };
	context::scope->clear();

	auto module = std::make_shared<decl::Module>("X");
	context::scope->insert("X", module);
	module->insert("Byte", type::Type::base_byte);
	Qual_Ident_Runner test2 { "X.Byte", qual_ident };
	context::clear();
}

TEST(Qual_Ident_Tests, incomplete) {
	sema::Qual_Ident qual_ident;
	auto module = std::make_shared<decl::Module>("X");
	context::scope->insert("X", module);
	Qual_Ident_Runner test1 { "X.", qual_ident, true };
	Qual_Ident_Runner test2 { ".", qual_ident, true, true };
	context::clear();
}