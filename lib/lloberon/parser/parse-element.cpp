#include "parser/parser.h"

void Parser::parse_element(expr::Const_Ptr& expression) {
	expr::Expression_Ptr element;
	parse_expression(element);
	auto const_element { expr::Const::as_const(element)};
	if (!const_element || !const_element->is_int()) {
		diag::report(diag::err_int_expected);
	}
	int begin = const_element->int_value();
	int end = begin;
	if (token::is(token::range)) {
		advance();
		parse_expression(element);
		const_element = expr::Const::as_const(element);
		if (!const_element || !const_element->is_int()) {
			diag::report(diag::err_int_expected);
		}
		end = const_element->int_value();
	}
	unsigned set { expression->set_value() };
	for (int i { begin }; i <= end; ++i) {
		set |= (1 << i);
	}
	expression = expr::Const::create(set);
}