#include "parser/parser.h"
#include "expr/binary.h"

bool Parser::check_0_int(const expr::Const& value) {
	if (value.int_value() == 0) { return report(diag::err_divide_by_0); }
	return false;
}

bool Parser::parse_term(sema::Expression& term) {
	if (parse_factor(term)) { return true; }
	auto value { term.expression };
	auto const_value { expr::Const::as_const(value) };

	while (token::is_one_of(
		token::star, token::slash, token::keyword_DIV,
		token::keyword_MOD, token::andop
	)) {
		auto op { token::kind };
		advance();
		if (parse_factor(term)) { return true; }
		auto right_value { term.expression };
		auto right_const_value { expr::Const::as_const(right_value) };
		if (const_value && right_const_value) {
			if (const_value->is_int() && right_const_value->is_int()) {
				auto lv { const_value->int_value() };
				auto rv { right_const_value->int_value() };
				switch (op) {
					case token::star:
						const_value = expr::Const::create(lv * rv); break;
					case token::slash:
						const_value = expr::Const::create(
							const_value->real_value() /
								right_const_value->real_value()
						);
						break;
					case token::keyword_DIV:
						if (check_0_int(*right_const_value)) { return true; }
						const_value = expr::Const::create(lv / rv);
						break;
					case token::keyword_MOD:
						if (check_0_int(*right_const_value)) { return true; }
						const_value = expr::Const::create(lv % rv);
						break;
					default:
						return report(diag::err_wrong_operator_for_int);
				}
				value = const_value;
			} else if (const_value->is_real() && right_const_value->is_real()) {
				auto lv { const_value->real_value() };
				auto rv { right_const_value->real_value() };
				double result;
				switch (op) {
					case token::star: result = lv * rv; break;
					case token::slash: result = lv / rv; break;
					default:
						return report(diag::err_wrong_operator_for_real);
				}
				const_value = expr::Const::create(result);
				value = const_value;
			} else if (const_value->is_bool() && right_const_value->is_bool()) {
				switch (op) {
					case token::andop:
						const_value = expr::Const::create(
							const_value->bool_value() &&
								right_const_value->bool_value()
						);
						value = const_value;
						break;
					default:
						return report(diag::err_wrong_operator_for_bool);
				}
			} else if (const_value->is_set() && right_const_value->is_set()) {
				auto lv { const_value->set_value() };
				auto rv { right_const_value->set_value() };
				unsigned result;
				switch (op) {
					case token::star: result = lv & rv; break;
					case token::slash: result = lv ^ rv; break;
					default:
						return report(diag::err_wrong_operator_for_set);
				}
				const_value = expr::Const::create(result);
				value = const_value;
			} else {
				return report(diag::err_wrong_operator_for_const);
			}
		} else {
			value = expr::Binary::create(op, value, right_value);
			const_value = nullptr;
		}
	}
	term.expression = value;
	return false;
}