#include "parser/parser.h"

void Parser::parse_actual_parameters() {
	consume(token::left_parenthesis);
	if (!token::is(token::right_parenthesis)) {
		expr::Expression_List expression_list;
		parse_expression_list(expression_list);
	}
	consume(token::right_parenthesis);
}