#include "parser/parser.h"

void Parser::parse_type_declaration() {
	sema::Ident_Def ident_def;
	parse_ident_def(ident_def);
	consume(token::equals);
	type::Type_Ptr type;
	parse_type(type);
	type->exported = ident_def.exported;
	if (!context::scope->insert(ident_def.ident, type)) {
		diag::report(diag::err_already_defined);
	}
}