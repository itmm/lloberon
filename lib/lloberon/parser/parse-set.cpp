#include "parser/parser.h"

void Parser::parse_set(expr::Const_Ptr& expression) {
	expression = expr::Const::create(0U);
	consume(token::left_brace);
	if (!token::is_one_of(token::right_brace, token::eof)) {
		parse_element(expression);
		while (token::is(token::comma)) {
			advance();
			parse_element(expression);
		}
	}
	consume(token::right_brace);
}