#include "parser/parser.h"

bool Parser::parse_expression(sema::Expression& expression) {
	if (parse_simple_expression(expression)) { return true; }
	auto value { expression.as_const() };
	while (token_.is_one_of(
		token::equals, token::not_equals, token::less, token::less_or_equal,
		token::greater, token::greater_or_equal, token::keyword_IS,
		token::keyword_IN
	)) {
		auto op { token_.kind() };
		advance();

		if (parse_simple_expression(expression)) { return true; }
		auto right_value { expression.as_const() };

		if (value && right_value) {
			if (value->is_int() && right_value->is_int()) {
				auto lv { value->int_value() }, rv { right_value->int_value() };
				bool result;
				switch (op) {
					case token::equals: result = (lv == rv); break;
					case token::not_equals: result = (lv != rv); break;
					case token::less: result = (lv < rv); break;
					case token::less_or_equal: result = (lv <= rv); break;
					case token::greater: result = (lv > rv); break;
					case token::greater_or_equal: result = (lv >= rv); break;
					default:
						diag().report(
							token_.location(), diag::err_wrong_operator_for_int
						);
						return true;
				}
				value = expr::Const::create(result);
			} else if (value->is_real() && right_value->is_real()) {
				auto lv { value->real_value() };
				auto rv { right_value->real_value() };
				bool result;
				switch (op) {
					case token::equals: result = (lv == rv); break;
					case token::not_equals: result = (lv != rv); break;
					case token::less: result = (lv < rv); break;
					case token::less_or_equal: result = (lv <= rv); break;
					case token::greater: result = (lv > rv); break;
					case token::greater_or_equal: result = (lv >= rv); break;
					default:
						diag().report(
							token_.location(), diag::err_wrong_operator_for_real
						);
						return true;
				}
				value = expr::Const::create(result);
			} else if (value->is_bool() && right_value->is_bool()) {
				auto lv { value->bool_value() };
				auto rv { right_value->bool_value() };
				bool result;
				switch (op) {
					case token::equals: result = (lv == rv); break;
					case token::not_equals: result = (lv != rv); break;
					default:
						diag().report(
							token_.location(), diag::err_wrong_operator_for_bool
						);
						return true;
				}
				value = expr::Const::create(result);
			} else {
				value = nullptr;
			}
		}
	}
	if (value) { expression.expression = value; }
	return false;
}