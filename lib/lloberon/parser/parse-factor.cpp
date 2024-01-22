#include "expr/const.h"
#include "parser/parser.h"
#include "expr/unary.h"

static int parse_int(const std::string& source, int base) {
	int value { 0 };
	for (const auto& ch: source) {
		int digit { -1 };
		if (ch >= '0' && ch <= '9') { digit = ch - '0'; }
		else if (ch >= 'A' && ch <= 'F') { digit = ch - 'A' + 10; }
		if (digit >= 0) {
			value = value * base + digit;
		}
	}
	return value;
}

void Parser::parse_factor(expr::Expression_Ptr& factor) {
	switch (token::kind) {
		case token::integer_literal: {
			std::string source { token::value };
			int base { source[source.length() - 1] == 'H' ? 16 : 10 };
			int value { parse_int(source, base) };
			advance();
			factor = expr::Const::create(value);
			break;
		}
		case token::float_literal: {
			double value = std::stod(token::value);
			advance();
			factor = expr::Const::create(value);
			break;
		}
		case token::string_literal: {
			std::string value { token::value };
			value = value.substr(1, value.size() - 2);
			factor = expr::Const::create(value);
			advance();
			break;
		}
		case token::char_literal: {
			std::string value { "_" };
			std::string source { token::value };
			int ch_value { parse_int(source, 16) };
			value[0] = static_cast<char>(ch_value);
			factor = expr::Const::create(value);
			advance();
			break;
		}
		case token::keyword_NIL:
			factor = expr::Expression::nil;
			advance();
			break;
		case token::keyword_TRUE:
			factor = expr::Const::create(true);
			advance();
			break;
		case token::keyword_FALSE:
			factor = expr::Const::create(false);
			advance();
			break;
		case token::left_brace: {
			expr::Const_Ptr const_expression;
			parse_set(const_expression);
			factor = const_expression;
			break;
		}
		case token::identifier: {
			parse_designator(factor);
			if (token::is(token::left_parenthesis)) {
				parse_actual_parameters();
			}
			break;
		}
		case token::left_parenthesis:
			advance();
			parse_expression(factor);
			consume(token::right_parenthesis);
			break;
		case token::notop: {
			advance();
			parse_expression(factor);
			auto value { expr::Const::as_const(factor) };
			if (value) {
				if (value->is_bool()) {
					factor = expr::Const::create(!value->bool_value());
				} else {
					diag::report(diag::err_wrong_operator_for_const);
				}
			} else {
				factor = expr::Unary::create(token::notop, factor);
			}
			break;
		}
		default:
			diag::report(diag::err_factor_expected);
	}
}