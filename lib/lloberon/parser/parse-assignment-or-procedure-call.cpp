#include "parser/parser.h"

bool Parser::parse_assignment_or_procedure_call(
	expr::Expression_Ptr& expression
) {
	expr::Expression_Ptr designator;
	if (parse_designator(designator)) { return true; }
	if (token::is(token::assign)) {
		advance();
		expr::Expression_Ptr rhs;
		if (parse_expression(rhs)) { return true; }
	} else {
		if (token::is(token::left_parenthesis)) {
			if (parse_actual_parameters()) { return true; }
		}
	}
	return false;
}