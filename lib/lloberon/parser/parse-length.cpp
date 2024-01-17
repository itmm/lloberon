#include "parser/parser.h"
#include "expr/const.h"

bool Parser::parse_length(sema::Length& length) {
	expr::Const_Ptr expression;
	if (parse_const_expression(expression)) { return true; }
	auto value { std::dynamic_pointer_cast<expr::Const>(expression) };
	if (!value || !value->is_int() || value->int_value() < 0) {
		return report(diag::err_length_must_be_nonnegative);
	}
	length.length = value->int_value();
	return false;
}