#include "parser/parser.h"
#include "expr/const.h"

bool Parser::parse_length(sema::Length& length) {
	sema::Const_Expression expression { length.context };
	if (parse_const_expression(expression)) { return true; }
	auto value {
		std::dynamic_pointer_cast<expr::Const>(expression.expression)
	};
	if (!value || !value->is_int() || value->int_value() < 0) {
		diag().report(token_.location(), diag::err_length_must_be_nonnegative);
		return true;
	}
	length.length = value->int_value();
	return false;
}