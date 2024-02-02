#include "parser/parser.h"

void Parser::parse_actual_parameters(expr::Call& call) {
	consume(token::left_parenthesis);
	if (!token::is(token::right_parenthesis)) {
		call.arguments = parse_expression_list();
	}
	consume(token::right_parenthesis);
}