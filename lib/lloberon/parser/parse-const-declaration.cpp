#include "parser/parser.h"

bool Parser::parse_const_declaration() {
	sema::Ident_Def ident_def;
	if (parse_ident_def(ident_def)) { return true; }
	if (consume(token::equals)) { return true; }
	Scope scope;
	sema::Const_Expression expression { scope };
	if (parse_const_expression(expression)) { return true; }
	// TODO: insert into scope
	return false;
}