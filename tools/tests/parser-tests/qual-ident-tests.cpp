#include "parser-tests.h"
#include "decl/type.h"
#include "type/base.h"

using Qual_Ident_Runner = Parser_Value_Runner<
	sema::Qual_Ident, &Parser::parse_qual_ident
>;

TEST(Qual_Ident_Tests, empty) {
	Scope scope;
	sema::Qual_Ident qual_ident { scope };
	Qual_Ident_Runner test1 { "", qual_ident, true };
}

TEST(Qual_Ident_Tests, simple) {
	Scope scope;
	decl::Type::register_base_types(scope);
	sema::Qual_Ident qual_ident { scope };
	Qual_Ident_Runner test1 { "BYTE", qual_ident };
	qual_ident.clear();
	new(&scope) Scope { };
	auto module = std::make_shared<decl::Module>("X");
	scope.insert("X", module);
	module->insert("Byte", std::make_shared<decl::Type>(
		std::make_shared<type::Base>(type::Base::bt_BYTE)
	));
	Qual_Ident_Runner test2 { "X.Byte", qual_ident };
}

TEST(Qual_Ident_Tests, incomplete) {
	Scope scope;
	sema::Qual_Ident qual_ident { scope };
	auto module = std::make_shared<decl::Module>("X");
	scope.insert("X", module);
	Qual_Ident_Runner test1 { "X.", qual_ident, true };

	qual_ident.clear();
	Qual_Ident_Runner test2 { ".", qual_ident, true, true };
}