#include "expr/const.h"
#include "parser/parser.h"
#include "expr/unary.h"
#include "expr/binary.h"

void Parser::parse_simple_expression(expr::Expression_Ptr& simple_expression) {
	bool is_negative { false };
	if (token::is_one_of(token::plus, token::minus)) {
		is_negative = token::is(token::minus);
		advance();
	}
	Scope scope;
	parse_term(simple_expression);

	auto value { simple_expression };
	auto const_value { expr::Const::as_const(value) };

	if (is_negative) {
		if (const_value) {
			if (const_value->is_int()) {
				const_value = expr::Const::create(-const_value->int_value());
				value = const_value;
			} else if (const_value->is_real()) {
				const_value = expr::Const::create(-const_value->real_value());
				value = const_value;
			} else {
				diag::report(diag::err_negate_must_be_numeric);
			}
		} else {
			value = expr::Unary::create(token::minus, value);
			const_value = nullptr;
		}
	}

	while (token::is_one_of(token::plus, token::minus, token::keyword_OR)) {
		auto op { token::kind };
		advance();
		parse_term(simple_expression);

		auto right_value { simple_expression };
		auto right_const_value { expr::Const::as_const(right_value) };

		if (const_value && right_const_value) {
			if (const_value->is_int() && right_const_value->is_int()) {
				auto lv { const_value->int_value() };
				auto rv { right_const_value->int_value() };
				int result;
				switch (op) {
					case token::plus: result = lv + rv; break;
					case token::minus: result = lv - rv; break;
					default:
						diag::report(diag::err_wrong_operator_for_int);
				}
				const_value = expr::Const::create(result);
				value = const_value;
			} else if (const_value->is_real() && right_const_value->is_real()) {
				auto lv { const_value->real_value() };
				auto rv { right_const_value->real_value() };
				double result;
				switch (op) {
					case token::plus: result = lv + rv; break;
					case token::minus: result = lv - rv; break;
					default:
						diag::report(diag::err_wrong_operator_for_real);
				}
				const_value = expr::Const::create(result);
				value = const_value;
			} else if (const_value->is_bool() && right_const_value->is_bool()) {
				if (op == token::keyword_OR) {
					const_value = expr::Const::create(
						const_value->bool_value() ||
						right_const_value->bool_value()
					);
					value = const_value;
				} else {
					diag::report(diag::err_wrong_operator_for_bool);
				}
			} else if (const_value->is_set() && right_const_value->is_set()) {
				auto lv { const_value->set_value() };
				auto rv { right_const_value->set_value() };
				unsigned result;
				switch (op) {
					case token::plus: result = lv | rv; break;
					case token::minus: result = lv - (lv & rv); break;
					default:
						diag::report(diag::err_wrong_operator_for_set);
				}
				const_value = expr::Const::create(result);
				value = const_value;
			} else { diag::report(diag::err_wrong_operator_for_const); }
		} else {
			value = expr::Binary::create(op, value, right_value);
			const_value = nullptr;
		}
	}

	simple_expression = value;
}