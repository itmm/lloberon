#include "parser/parser.h"

bool Parser::parse_actual_parameters() {
	if (consume(token::left_parenthesis)) { return true; }
	if (!token::is(token::right_parenthesis)) {
		expr::Expression_List expression_list;
		if (parse_expression_list(expression_list)) { return true; }
	}
	if (consume(token::right_parenthesis)) { return true; }
	return false;
}