#include "parser/parser.h"

void Parser::parse_assignment_or_procedure_call(
	expr::Expression_Ptr& expression
) {
	expression = parse_designator();
	if (token::is(token::assign)) {
		advance();
		expr::Expression_Ptr rhs { parse_expression() };
	} else {
		if (token::is(token::left_parenthesis)) {
			parse_actual_parameters();
		}
	}
}