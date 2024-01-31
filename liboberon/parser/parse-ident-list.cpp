#include "parser/parser.h"
#include "sema/ident-def.h"

sema::Ident_List Parser::parse_ident_list() {
	sema::Ident_List ident_list;
	sema::Ident_Def ident_def { parse_ident_def() };
	ident_list.push_back(ident_def);
	while (token::is(token::comma)) {
		advance();
		ident_def = parse_ident_def();
		ident_list.push_back(ident_def);
	}
	return ident_list;
}