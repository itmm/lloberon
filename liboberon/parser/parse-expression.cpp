#include "parser/parser.h"
#include "expr/binary.h"

expr::Expression_Ptr Parser::parse_expression() {
	expr::Expression_Ptr value { parse_simple_expression() };
	auto const_value { expr::Const::as_const(value) };
	while (token::is_one_of(
		token::equals, token::not_equals, token::less, token::less_or_equal,
		token::greater, token::greater_or_equal, token::keyword_IS,
		token::keyword_IN
	)) {
		auto op { token::kind };
		advance();

		if (op == token::keyword_IS) {
			auto type { type::Type::as_type(parse_qual_ident()) };
			if (!type) {
				diag::report(diag::err_type_expected);
			}
			continue;
		}
		expr::Expression_Ptr right_value { parse_simple_expression() };
		auto right_const_value { expr::Const::as_const(right_value) };

		if (const_value && right_const_value) {
			if (const_value->is_int() && right_const_value->is_int()) {
				auto lv { const_value->int_value() };
				auto rv { right_const_value->int_value() };
				bool result;
				switch (op) {
					case token::equals: result = (lv == rv); break;
					case token::not_equals: result = (lv != rv); break;
					case token::less: result = (lv < rv); break;
					case token::less_or_equal: result = (lv <= rv); break;
					case token::greater: result = (lv > rv); break;
					case token::greater_or_equal: result = (lv >= rv); break;
					default:
						diag::report(diag::err_wrong_operator_for_int);
				}
				const_value = expr::Const::create(result);
				value = const_value;
			} else if (const_value->is_real() && right_const_value->is_real()) {
				auto lv { const_value->real_value() };
				auto rv { right_const_value->real_value() };
				bool result;
				switch (op) {
					case token::equals: result = (lv == rv); break;
					case token::not_equals: result = (lv != rv); break;
					case token::less: result = (lv < rv); break;
					case token::less_or_equal: result = (lv <= rv); break;
					case token::greater: result = (lv > rv); break;
					case token::greater_or_equal: result = (lv >= rv); break;
					default:
						diag::report(diag::err_wrong_operator_for_real);
				}
				const_value = expr::Const::create(result);
				value = const_value;
			} else if (const_value->is_bool() && right_const_value->is_bool()) {
				auto lv { const_value->bool_value() };
				auto rv { right_const_value->bool_value() };
				bool result;
				switch (op) {
					case token::equals: result = (lv == rv); break;
					case token::not_equals: result = (lv != rv); break;
					default:
						diag::report(diag::err_wrong_operator_for_bool);
				}
				const_value = expr::Const::create(result);
				value = const_value;
			} else if (const_value->is_set() && right_const_value->is_set()) {
				auto lv { const_value->set_value() };
				auto rv { right_const_value->set_value() };
				bool result;
				switch (op) {
					case token::equals: result = (lv == rv); break;
					case token::not_equals: result = (lv != rv); break;
					default:
						diag::report(diag::err_wrong_operator_for_set);
				}
				const_value = expr::Const::create(result);
				value = const_value;
			} else if (const_value->is_int() && right_const_value->is_set()) {
				auto lv { const_value->int_value() };
				auto rv { right_const_value->set_value() };
				bool result;
				switch (op) {
					case token::keyword_IN:
						result = (((1 << lv) & rv) != 0); break;
					default:
						diag::report(diag::err_wrong_operator_for_set);
				}
				const_value = expr::Const::create(result);
				value = const_value;
			} else {
				diag::report(diag::err_wrong_operator_for_const);
			}
		} else {
			value = expr::Binary::create(op, value, right_value);
			const_value = nullptr;
		}
	}
	return value;
}