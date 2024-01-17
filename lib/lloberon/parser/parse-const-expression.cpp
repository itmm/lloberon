#include "parser/parser.h"

bool Parser::parse_const_expression(sema::Const_Expression& const_expression) {
	sema::Expression expression;
	if (parse_expression(expression)) { return true; }
	auto const_value {
		std::dynamic_pointer_cast<expr::Const>(expression.expression)
	};
	if (!const_value) {
		return report(diag::err_const_experssion_expected);
	}
	const_expression.expression = const_value;
	return false;
}