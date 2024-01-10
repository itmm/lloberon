#include "parser/parser.h"
#include "sema/expression.h"
#include "expr/integer.h"
#include "expr/bool.h"

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
        case token::float_literal: case token::string_literal:
        case token::keyword_NIL:
            advance();
            break;
        case token::keyword_TRUE: case token::keyword_FALSE:
            factor.expression = std::make_shared<expr::Bool>(token_.kind() == token::keyword_TRUE);
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
            sema::Expression expression{scope};
            if (parse_expression(expression)) { return true; }
            if (consume(token::right_parenthesis)) { return true; }
            break;
        }
        default:
            error();
            return true;
    }
    return false;
}