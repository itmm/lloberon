#include "parser/parser.h"

#include "expr/label.h"

bool Parser::parse_label(sema::Const_Label& label) {
	if (token::is_one_of(token::integer_literal, token::string_literal)) {
		sema::Expression expression { label.context };
		if (parse_factor(expression)) { return true; }
		label.value = expr::Const::as_const(expression.expression);
	} else {
		return report(diag::err_const_label_expected);
	}
	return false;
}
