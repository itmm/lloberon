#include "parser/parser.h"

void Parser::parse_type_declaration() {
	sema::Ident_Def ident_def { parse_ident_def() };
	consume(token::equals);
	auto type { parse_type() };
	type->exported = ident_def.exported;
	if (!context::scope->insert(ident_def.ident, type)) {
		diag::report(diag::err_already_defined);
	}
}