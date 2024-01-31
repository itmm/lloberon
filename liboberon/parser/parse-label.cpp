#include "parser/parser.h"

#include "expr/label.h"

expr::Const_Ptr Parser::parse_label() {
	if (token::is_one_of(token::integer_literal, token::string_literal)) {
		auto expression { parse_factor() };
		return expr::Const::as_const(expression);
	} else {
		diag::report(diag::err_const_label_expected);
	}
}
