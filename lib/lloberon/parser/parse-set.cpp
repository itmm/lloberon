#include "parser/parser.h"

void Parser::parse_set(expr::Const_Ptr& expression) {
	expression = expr::Const::create(0U);
	consume(token::left_brace);
	unsigned set_value { 0 };
	if (!token::is_one_of(token::right_brace, token::eof)) {
		parse_element(set_value);
		while (token::is(token::comma)) {
			advance();
			parse_element(set_value);
		}
	}
	consume(token::right_brace);
	expression = expr::Const::create(set_value);
}