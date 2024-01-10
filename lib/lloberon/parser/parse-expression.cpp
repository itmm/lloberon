#include "parser/parser.h"

bool Parser::parse_expression(sema::Expression& expression) {
	if (parse_simple_expression(expression)) { return true; }
	while (token_.is_one_of(
		token::equals, token::not_equals, token::less, token::less_or_equal,
		token::greater, token::greater_or_equal, token::keyword_IS,
		token::keyword_IN
	)) {
		advance();
		if (parse_simple_expression(expression)) { return true; }
	}
	return false;
}