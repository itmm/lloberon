#include "parser/parser.h"

void Parser::parse_const_declaration() {
	auto ident_def { parse_ident_def() };
	consume(token::equals);
	auto expression { parse_const_expression() };
	expression->exported = ident_def.exported;
	if (!context::scope->insert(ident_def.ident, expression)) {
		report(diag::err_already_defined, ident_def.ident);
	}
}