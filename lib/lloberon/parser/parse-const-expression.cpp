#include "parser/parser.h"

bool Parser::parse_const_expression(expr::Const_Ptr& const_expression) {
	expr::Expression_Ptr expression;
	if (parse_expression(expression)) { return true; }
	auto const_value { std::dynamic_pointer_cast<expr::Const>(expression) };
	if (!const_value) {
		return report(diag::err_const_experssion_expected);
	}
	const_expression = const_value;
	return false;
}