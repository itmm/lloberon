#include "parser/parser.h"

bool Parser::parse_const_declaration() {
	sema::Ident_Def ident_def;
	if (parse_ident_def(ident_def)) { return true; }
	if (consume(token::equals)) { return true; }
	expr::Const_Ptr expression;
	if (parse_const_expression(expression)) { return true; }
	expression->exported = ident_def.exported;
	if (!context::scope->insert(ident_def.ident, expression)) {
		return report(diag::err_already_defined, ident_def.ident);
	}
	return false;
}