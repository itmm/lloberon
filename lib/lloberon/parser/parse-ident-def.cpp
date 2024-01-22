#include "parser/parser.h"
#include "sema/ident-def.h"

void Parser::parse_ident_def(sema::Ident_Def& ident_def) {
	expect(token::identifier);
	ident_def.ident = token::value;
	advance();
	ident_def.exported = token::is(token::star);
	if (ident_def.exported) {
		advance();
	}
}