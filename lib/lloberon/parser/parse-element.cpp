#include "parser/parser.h"

bool Parser::parse_element(expr::Const_Ptr& expression) {
	sema::Expression element;
	if (parse_expression(element)) { return true; }
	auto const_element { expr::Const::as_const(element.expression)};
	if (!const_element || !const_element->is_int()) {
		return report(diag::err_int_expected);
	}
	int begin = const_element->int_value();
	int end = begin;
	if (token::is(token::range)) {
		advance();
		if (parse_expression(element)) { return true; }
		const_element = expr::Const::as_const(element.expression);
		if (!const_element || !const_element->is_int()) {
			return report(diag::err_int_expected);
		}
		end = const_element->int_value();
	}
	unsigned set { expression->set_value() };
	for (int i { begin }; i <= end; ++i) {
		set |= (1 << i);
	}
	expression = expr::Const::create(set);
	return false;
}