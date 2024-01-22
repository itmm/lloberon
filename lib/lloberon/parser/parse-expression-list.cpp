#include "parser/parser.h"

void Parser::parse_expression_list(expr::Expression_List& expression_list) {
	expression_list.push_back(parse_expression());
	while (token::is(token::comma)) {
		advance();
		expression_list.push_back(parse_expression());
	}
}