#include "parser/parser.h"

using namespace lloberon;

bool Parser::parse_set() {
    if (consume(token::left_brace)) { return true; }
    if (! token_.is_one_of(token::right_brace, token::eof)) {
        if (parse_element()) { return true; }
        while (token_.is(token::comma)) {
            advance();
            if (parse_element()) { return true; }
        }
    }
    if (consume(token::right_brace)) { return true ; }
    return false;
}