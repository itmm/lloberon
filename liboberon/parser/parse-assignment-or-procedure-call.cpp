#include "parser/parser.h"
#include "expr/call.h"

void Parser::parse_assignment_or_procedure_call(
	expr::Expression_Ptr& expression
) {
	expression = parse_designator();
	if (token::is(token::assign)) {
		advance();
		expr::Expression_Ptr rhs { parse_expression() };
	} else {
		if (token::is(token::left_parenthesis)) {
			auto call { expr::Call::as_call(expression) };
			if (!call) { diag::report(diag::err_procedure_expected); }
			parse_actual_parameters(*call);
		}
	}
}