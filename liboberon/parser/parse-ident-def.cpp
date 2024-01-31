#include "parser/parser.h"
#include "sema/ident-def.h"

sema::Ident_Def Parser::parse_ident_def() {
	expect(token::identifier);
	sema::Ident_Def ident_def;
	ident_def.ident = token::value;
	advance();
	ident_def.exported = token::is(token::star);
	if (ident_def.exported) {
		advance();
	}
	return ident_def;
}