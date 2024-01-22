#include "parser/parser.h"

void Parser::parse_const_expression(expr::Const_Ptr& const_expression) {
	expr::Expression_Ptr expression;
	parse_expression(expression);
	auto const_value { std::dynamic_pointer_cast<expr::Const>(expression) };
	if (!const_value) {
		diag::report(diag::err_const_experssion_expected);
	}
	const_expression = const_value;
}