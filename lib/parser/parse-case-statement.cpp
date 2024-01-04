#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_case_statement() {
    if (consume(token::keyword_CASE)) { return true; }
    if (parse_expression()) { return true; }
    if (consume(token::keyword_OF)) { return true; }
    if (parse_case()) { return true; }
    while (token_.is(token::bar)) {
        advance();
        if (parse_case()) { return true; }
    }
    if (consume(token::keyword_END)) { return true; }
    return false;
}