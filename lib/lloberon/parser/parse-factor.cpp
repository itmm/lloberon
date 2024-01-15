#include "expr/const.h"
#include "parser/parser.h"
#include "sema/expression.h"
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

bool Parser::parse_factor(sema::Expression& factor) {
	switch (token_.kind()) {
		case token::integer_literal: {
			std::string source { token_.literal_data().str() };
			int base { source[source.length() - 1] == 'H' ? 16 : 10 };
			int value { parse_int(source, base) };
			advance();
			factor.expression = expr::Const::create(value);
			break;
		}
		case token::float_literal: {
			double value = std::stod(token_.literal_data().str());
			advance();
			factor.expression = expr::Const::create(value);
			break;
		}
		case token::string_literal: {
			std::string value { token_.literal_data().str() };
			value = value.substr(1, value.size() - 2);
			factor.expression = expr::Const::create(value);
			advance();
			break;
		}
		case token::char_literal: {
			std::string value { "_" };
			std::string source { token_.literal_data().str() };
			int ch_value { parse_int(source, 16) };
			value[0] = static_cast<char>(ch_value);
			factor.expression = expr::Const::create(value);
			advance();
			break;
		}
		case token::keyword_NIL:
			factor.expression = expr::Expression::nil;
			advance();
			break;
		case token::keyword_TRUE:
			factor.expression = expr::Const::create(true);
			advance();
			break;
		case token::keyword_FALSE:
			factor.expression = expr::Const::create(false);
			advance();
			break;
		case token::left_brace: {
			sema::Const_Expression const_expression { factor.context };
			if (parse_set(const_expression)) { return true; }
			factor.expression = const_expression.expression;
			break;
		}
		case token::identifier: {
			sema::Designator designator { factor.context };
			if (parse_designator(designator)) { return true; }
			if (token_.is(token::left_parenthesis)) {
				Context context;
				sema::Actual_Parameters actual_parameters { context };
				if (parse_actual_parameters(actual_parameters)) { return true; }
			}
			factor.expression = std::make_shared<expr::Expression>(nullptr);
			break;
		}
		case token::left_parenthesis:
			advance();
			if (parse_expression(factor)) { return true; }
			if (consume(token::right_parenthesis)) { return true; }
			break;
		case token::notop: {
			advance();
			if (parse_expression(factor)) { return true; }
			auto value { expr::Const::as_const(factor.expression) };
			if (value) {
				if (value->is_bool()) {
					factor.expression = expr::Const::create(
						!value->bool_value()
					);
				} else {
					diag().report(
						token_.location(), diag::err_wrong_operator_for_const
					);
					return true;
				}
			} else {
				factor.expression = expr::Unary::create(
					token::notop, factor.expression
				);
			}
			break;
		}
		default:
			diag().report(token_.location(), diag::err_factor_expected);
			return true;
	}
	return false;
}