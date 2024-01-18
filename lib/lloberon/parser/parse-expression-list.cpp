#include "parser/parser.h"

bool Parser::parse_expression_list(expr::Expression_List& expression_list) {
	expr::Expression_Ptr expression;
	if (parse_expression(expression)) { return true; }
	expression_list.push_back(expression);
	while (token::is(token::comma)) {
		advance();
		if (parse_expression(expression)) { return true; }
		expression_list.push_back(expression);
	}
	return false;
}