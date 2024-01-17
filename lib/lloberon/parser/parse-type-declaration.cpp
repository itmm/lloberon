#include "parser/parser.h"

bool Parser::parse_type_declaration() {
	sema::Ident_Def ident_def;
	if (parse_ident_def(ident_def)) { return true; }
	if (consume(token::equals)) { return true; }
	type::Type_Ptr type;
	if (parse_type(type)) { return true; }
	auto declaration { std::make_shared<decl::Type>(type) };
	declaration->exported = ident_def.exported;
	if (!context::scope->insert(ident_def.ident, declaration)) {
		return report(diag::err_already_defined);
	}
	return false;
}