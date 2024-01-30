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

expr::Expression_Ptr Parser::parse_factor() {
	switch (token::kind) {
		case token::integer_literal: {
			std::string source { token::value };
			int base { source[source.length() - 1] == 'H' ? 16 : 10 };
			int value { parse_int(source, base) };
			advance();
			return expr::Const::create(value);
		}
		case token::float_literal: {
			double value = std::stod(token::value);
			advance();
			return expr::Const::create(value);
		}
		case token::string_literal: {
			std::string value { token::value };
			value = value.substr(1, value.size() - 2);
			advance();
			return expr::Const::create(value);
		}
		case token::char_literal: {
			std::string value { "_" };
			std::string source { token::value };
			int ch_value { parse_int(source, 16) };
			value[0] = static_cast<char>(ch_value);
			advance();
			return expr::Const::create(value);
		}
		case token::keyword_NIL:
			advance();
			return expr::Expression::nil;
		case token::keyword_TRUE:
			advance();
			return expr::Const::create(true);
		case token::keyword_FALSE:
			advance();
			return expr::Const::create(false);
		case token::left_brace:
			return parse_set();
		case token::identifier: {
			expr::Expression_Ptr factor { parse_designator() };
			if (token::is(token::left_parenthesis)) {
				parse_actual_parameters();
			}
			return factor;
		}
		case token::left_parenthesis: {
			advance();
			auto inner { parse_expression() };
			consume(token::right_parenthesis);
			return inner;
		}
		case token::notop: {
			advance();
			auto factor { parse_expression() };
			auto value { expr::Const::as_const(factor) };
			if (value) {
				if (value->is_bool()) {
					return expr::Const::create(!value->bool_value());
				} else { diag::report(diag::err_wrong_operator_for_const); }
			} else { return expr::Unary::create(token::notop, factor); }
		}
		default:
			diag::report(diag::err_factor_expected);
	}
}