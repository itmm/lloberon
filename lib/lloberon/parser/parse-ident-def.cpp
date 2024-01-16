#include "parser/parser.h"
#include "sema/ident-def.h"

bool Parser::parse_ident_def(sema::Ident_Def& ident_def) {
	new(&ident_def) sema::Ident_Def { };
	if (expect(token::identifier)) { return true; }
	ident_def.ident = token::value;
	advance();
	if (token::is(token::star)) {
		ident_def.exported = true;
		advance();
	}
	return false;
}