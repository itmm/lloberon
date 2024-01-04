#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_formal_parameters() {
    if (consume(token::left_parenthesis)) { return true; }
    if (!token_.is(token::right_parenthesis)) {
        if (parse_formal_parameter_section()) { return true; }
        while (token_.is(token::semicolon)) {
            advance();
            if (parse_formal_parameter_section()) { return true; }
        }
    }
    if (consume(token::right_parenthesis)) { return true; }
    if (token_.is(token::colon)) {
        advance();
        if (parse_qual_ident()) { return true; }
    }
    return false;
}