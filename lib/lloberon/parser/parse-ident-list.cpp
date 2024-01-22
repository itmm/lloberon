#include "parser/parser.h"
#include "sema/ident-def.h"

void Parser::parse_ident_list(sema::Ident_List& ident_list) {
	ident_list.clear();
	sema::Ident_Def ident_def;
	parse_ident_def(ident_def);
	ident_list.push_back(ident_def);
	while (token::is(token::comma)) {
		advance();
		parse_ident_def(ident_def);
		ident_list.emplace_back(ident_def.ident, ident_def.exported);
	}
}