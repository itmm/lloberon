#include "parser/parser.h"

void Parser::parse_actual_parameters() {
	consume(token::left_parenthesis);
	if (!token::is(token::right_parenthesis)) {
		auto expression_list { parse_expression_list() };
	}
	consume(token::right_parenthesis);
}