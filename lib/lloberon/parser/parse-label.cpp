#include "parser/parser.h"

#include "expr/label.h"

void Parser::parse_label(expr::Const_Ptr& label) {
	if (token::is_one_of(token::integer_literal, token::string_literal)) {
		auto expression { parse_factor() };
		label = expr::Const::as_const(expression);
	} else {
		diag::report(diag::err_const_label_expected);
	}
}
