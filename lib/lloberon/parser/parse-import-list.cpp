#include "parser/parser.h"

bool Parser::parse_import_list(Scope& scope) {
	if (consume(token::keyword_IMPORT)) { return true; }
	if (parse_import(scope)) { return true; }
	while (token::is(token::comma)) {
		advance();
		if (parse_import(scope)) { return true; }
	}
	if (consume(token::semicolon)) { return true; }
	return false;
}