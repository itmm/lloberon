#include "parser/parser.h"

bool Parser::parse_label(sema::Const_Label& label) {
	if (token_.is_one_of(token::integer_literal, token::string_literal)) {
		sema::Expression expression { label.scope() };
		if (parse_factor(expression)) { return true; }
		label.value = expr::Const::as_const(expression.expression);
	} else {
		diag().report(token_.location(), diag::err_const_label_expected);
		return true;
	}
	return false;
}

bool Parser::parse_label(sema::Type_Label& label) {
	sema::Qual_Ident qual_ident { label.scope() };
	if (parse_qual_ident(qual_ident)) { return true; }
	return false;
}