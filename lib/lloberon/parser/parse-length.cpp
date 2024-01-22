#include "parser/parser.h"
#include "expr/const.h"

int Parser::parse_length() {
	auto value { parse_const_expression() };
	if (!value || !value->is_int() || value->int_value() < 0) {
		diag::report(diag::err_length_must_be_nonnegative);
	}
	return value->int_value();
}