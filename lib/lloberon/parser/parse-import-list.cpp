#include "parser/parser.h"

void Parser::parse_import_list(Scope& scope) {
	consume(token::keyword_IMPORT);
	parse_import(scope);
	while (token::is(token::comma)) {
		advance();
		parse_import(scope);
	}
	consume(token::semicolon);
}