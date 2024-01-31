#include "parser/parser.h"

expr::Const_Ptr Parser::parse_set() {
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
	return expr::Const::create(set_value);
}