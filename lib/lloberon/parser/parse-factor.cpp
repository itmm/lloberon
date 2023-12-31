#include "parser/parser.h"
#include "sema/factor.h"

bool Parser::parse_factor(sema::Factor& factor) {
    factor.clear();
    switch (token_.kind()) {
        case token::integer_literal: case token::float_literal: case token::string_literal:
        case token::keyword_NIL: case token::keyword_TRUE: case token::keyword_FALSE:
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