#include "parser/parser.h"

bool Parser::check_0_int(const expr::Const& value) {
	if (value.int_value() == 0) {
		diag().report(token_.location(), diag::err_divide_by_0);
		return true;
	}
	return false;
}

bool Parser::parse_term(sema::Expression& term) {
	if (parse_factor(term)) { return true; }
	auto value { term.as_const() };

	while (token_.is_one_of(
		token::star, token::slash, token::keyword_DIV,
		token::keyword_MOD, token::andop
	)) {
		auto op { token_.kind() };
		advance();
		if (parse_factor(term)) { return true; }
		auto right_value { term.as_const() };
		if (value && right_value) {
			if (value->is_int() && right_value->is_int()) {
				auto lv { value->int_value() }, rv { right_value->int_value() };
				switch (op) {
					case token::star:
						value = expr::Const::create(lv * rv); break;
					case token::slash:
						value = expr::Const::create(
							value->real_value() / right_value->real_value()
						);
						break;
					case token::keyword_DIV:
						if (check_0_int(*right_value)) { return true; }
						value = expr::Const::create(lv / rv);
						break;
					case token::keyword_MOD:
						if (check_0_int(*right_value)) { return true; }
						value = expr::Const::create(lv % rv);
						break;
					default:
						diag().report(
							token_.location(), diag::err_wrong_operator_for_int
						);
						return true;
				}
			} else if (value->is_real() && right_value->is_real()) {
				auto lv { value->real_value() };
				auto rv { right_value->real_value() };
				double result;
				switch (op) {
					case token::star: result = lv * rv; break;
					case token::slash: result = lv / rv; break;
					default:
						diag().report(
							token_.location(), diag::err_wrong_operator_for_real
						);
						return true;
				}
				value = expr::Const::create(result);
			} else if (value->is_bool() && right_value->is_bool()) {
				switch (op) {
					case token::andop:
						value = expr::Const::create(
							value->bool_value() && right_value->bool_value()
						);
						break;
					default:
						diag().report(
							token_.location(), diag::err_wrong_operator_for_bool
						);
						return true;
				}
			}
		}
	}
	if (value) { term.expression = value ;}
	return false;
}