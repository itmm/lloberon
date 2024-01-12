#include "expr/const.h"
#include "parser/parser.h"

bool Parser::parse_simple_expression(sema::Expression& simple_expression) {
	bool is_negative { false };
	if (token_.is_one_of(token::plus, token::minus)) {
		is_negative = token_.is(token::minus);
		advance();
	}
	Scope scope;
	if (parse_term(simple_expression)) { return true; }

	auto value { expr::Const::as_const(simple_expression.expression) };

	if (is_negative) {
		if (value) {
			if (value->is_int()) {
				value = expr::Const::create(-value->int_value());
			} else if (value->is_real()) {
				value = expr::Const::create(-value->real_value());
			} else {
				diag().report(
					token_.location(), diag::err_negate_must_be_numeric
				);
				return true;
			}
		}
	}

	while (token_.is_one_of(token::plus, token::minus, token::keyword_OR)) {
		auto op { token_.kind() };
		advance();
		if (parse_term(simple_expression)) { return true; }

		auto right_value { expr::Const::as_const(
			simple_expression.expression
		) };

		if (value && right_value) {
			if (value->is_int() && right_value->is_int()) {
				auto lv { value->int_value() }, rv { right_value->int_value() };
				int result;
				switch (op) {
					case token::plus: result = lv + rv; break;
					case token::minus: result = lv - rv; break;
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
				double result;
				switch (op) {
					case token::plus: result = lv + rv; break;
					case token::minus: result = lv - rv; break;
					default:
						diag().report(
							token_.location(), diag::err_wrong_operator_for_real
						);
						return true;
				}
				value = expr::Const::create(result);
			} else if (value->is_bool() && right_value->is_bool()) {
				if (op == token::keyword_OR) {
					value = expr::Const::create(
						value->bool_value() || right_value->bool_value()
					);
				} else {
					diag().report(
						token_.location(), diag::err_wrong_operator_for_bool
					);
					return true;
				}
			} else {
				value = nullptr;
			}
		}
	}

	if (value) { simple_expression.expression = value; }

	return false;
}