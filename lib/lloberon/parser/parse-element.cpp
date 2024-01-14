#include "parser/parser.h"

bool Parser::parse_element(sema::Const_Expression& expression) {
	Scope scope;
	sema::Expression element { scope };
	if (parse_expression(element)) { return true; }
	auto const_element { expr::Const::as_const(element.expression)};
	if (!const_element || !const_element->is_int()) {
		diag().report(token_.location(), diag::err_int_expected);
		return true;
	}
	int begin = const_element->int_value();
	int end = begin;
	if (token_.is(token::range)) {
		advance();
		if (parse_expression(element)) { return true; }
		const_element = expr::Const::as_const(element.expression);
		if (!const_element || !const_element->is_int()) {
			diag().report(token_.location(), diag::err_int_expected);
			return true;
		}
		end = const_element->int_value();
	}
	unsigned set { expression.expression->set_value() };
	for (int i { begin }; i <= end; ++i) {
		set |= (1 << i);
	}
	expression.expression = expr::Const::create(set);
	return false;
}