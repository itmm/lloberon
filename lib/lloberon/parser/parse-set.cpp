#include "parser/parser.h"

bool Parser::parse_set(expr::Const_Ptr& expression) {
	expression = expr::Const::create(0U);
	if (consume(token::left_brace)) { return true; }
	if (!token::is_one_of(token::right_brace, token::eof)) {
		if (parse_element(expression)) { return true; }
		while (token::is(token::comma)) {
			advance();
			if (parse_element(expression)) { return true; }
		}
	}
	if (consume(token::right_brace)) { return true; }
	return false;
}