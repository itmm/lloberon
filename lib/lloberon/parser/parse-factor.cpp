#include "expr/const.h"
#include "parser/parser.h"
#include "sema/expression.h"
#include "expr/unary.h"

bool Parser::parse_factor(sema::Expression& factor) {
	factor.clear();
	switch (token_.kind()) {
		case token::integer_literal: {
			int value { 0 };
			for (const auto& ch : token_.literal_data()) {
				value = value * 10 + (ch - '0');
			}
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
		case token::string_literal:
			advance();
			break;
		case token::keyword_NIL:
			factor.expression = expr::Expression::nil;
			advance();
			break;
		case token::keyword_TRUE:
		case token::keyword_FALSE:
			factor.expression = expr::Const::create(
				token_.kind() == token::keyword_TRUE
			);
			advance();
			break;
		case token::left_brace:
			if (parse_set()) { return true; }
			break;

		case token::identifier: {
			sema::Designator designator { factor.scope() };
			if (parse_designator(designator)) { return true; }
			if (token_.is(token::left_parenthesis)) {
				sema::Actual_Parameters actual_parameters { factor.scope() };
				if (parse_actual_parameters(actual_parameters)) { return true; }
			}
			factor.expression = std::make_shared<expr::Expression>(nullptr);
			break;
		}
		case token::left_parenthesis:
			advance();
			if (parse_expression(factor)) { return true; }
			if (consume(token::right_parenthesis)) {
				factor.clear(); return true;
			}
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