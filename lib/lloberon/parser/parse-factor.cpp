#include "expr/bool.h"
#include "expr/integer.h"
#include "expr/nil.h"
#include "expr/real.h"
#include "parser/parser.h"
#include "sema/expression.h"

bool Parser::parse_factor(sema::Expression& factor) {
	factor.clear();
	switch (token_.kind()) {
		case token::integer_literal: {
			int value { 0 };
			for (const auto& ch : token_.literal_data()) {
				value = value * 10 + (ch - '0');
			}
			advance();
			factor.expression = std::make_shared<expr::Integer>(value);
			break;
		}
		case token::float_literal: {
			double value = std::stod(token_.literal_data().str());
			advance();
			factor.expression = std::make_shared<expr::Real>(value);
			break;
		}
		case token::string_literal:
			advance();
			break;
		case token::keyword_NIL:
			factor.expression = std::make_shared<expr::Nil>();
			advance();
			break;
		case token::keyword_TRUE:
		case token::keyword_FALSE:
			factor.expression = std::make_shared<expr::Bool>(
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
			break;
		}
		case token::left_parenthesis: {
			advance();
			Scope scope;
			sema::Expression expression { scope };
			if (parse_expression(expression)) { return true; }
			if (consume(token::right_parenthesis)) { return true; }
			break;
		}
		default:
			diag().report(token_.location(), diag::err_factor_expected);
			return true;
	}
	return false;
}