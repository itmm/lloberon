#include "parser/parser.h"

#include "expr/label.h"

bool Parser::parse_label(expr::Const_Ptr& label) {
	if (token::is_one_of(token::integer_literal, token::string_literal)) {
		expr::Expression_Ptr expression;
		if (parse_factor(expression)) { return true; }
		label = expr::Const::as_const(expression);
	} else {
		return report(diag::err_const_label_expected);
	}
	return false;
}
