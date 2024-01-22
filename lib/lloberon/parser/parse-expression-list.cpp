#include "parser/parser.h"

void Parser::parse_expression_list(expr::Expression_List& expression_list) {
	expr::Expression_Ptr expression;
	parse_expression(expression);
	expression_list.push_back(expression);
	while (token::is(token::comma)) {
		advance();
		parse_expression(expression);
		expression_list.push_back(expression);
	}
}