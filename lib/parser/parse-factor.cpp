#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_factor() {
    switch (token_.kind()) {
        case token::integer_literal: case token::float_literal: case token::string_literal:
        case token::keyword_NIL: case token::keyword_TRUE: case token::keyword_FALSE:
            advance();
            break;
        case token::left_brace:
            if (parse_set()) { return true; }
            break;

        case token::identifier:
            if (parse_designator()) { return true; }
            if (token_.is(token::left_parenthesis)) {
                if (parse_actual_parameters()) { return true; }
            }
            break;
        case token::left_parenthesis:
            advance();
            if (parse_expression()) { return true; }
            if (!consume(token::right_parenthesis)) { break; }
        LLVM_FALLTHROUGH; default:
            while (!token_.is_one_of(
                token::right_parenthesis, token::plus, token::minus,
                token::slash, token::star, token::eof
            )) {
                advance();
            }
            error();
            return true;
    }
    return false;
}