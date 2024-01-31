#include "parser/parser.h"

void Parser::parse_element(unsigned& set_value) {
	auto element { parse_expression() };
	auto const_element { expr::Const::as_const(element)};
	if (!const_element || !const_element->is_int()) {
		diag::report(diag::err_int_expected);
	}
	int begin = const_element->int_value();
	int end = begin;
	if (token::is(token::range)) {
		advance();
		element = parse_expression();
		const_element = expr::Const::as_const(element);
		if (!const_element || !const_element->is_int()) {
			diag::report(diag::err_int_expected);
		}
		end = const_element->int_value();
	}
	for (int i { begin }; i <= end; ++i) {
		set_value |= (1 << i);
	}
}