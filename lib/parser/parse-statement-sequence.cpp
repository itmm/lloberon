#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_statement_sequence() {
    if (parse_statement()) { return true; }
    while (token_.is(token::semicolon)) {
        advance();
        if (parse_statement()) { return true; }
    }
    return false;
}