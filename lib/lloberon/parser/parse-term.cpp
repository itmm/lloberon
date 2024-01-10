#include "parser/parser.h"

bool Parser::parse_term(sema::Expression& term) {
	if (parse_factor(term)) { return true; }
	while (token_.is_one_of(
		token::star, token::slash, token::keyword_DIV,
		token::keyword_MOD, token::andop
	)) {
		advance();
		if (parse_factor(term)) { return true; }
	}
	return false;
}