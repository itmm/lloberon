#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_while_statement() {
    if (consume(token::keyword_WHILE)) { return true; }
    if (parse_expression()) { return true; }
    if (consume(token::keyword_DO)) { return true; }
    if (parse_statement_sequence()) { return true; }
    while (token_.is(token::keyword_ELSIF)) {
        advance();
        if (parse_expression()) { return true; }
        if (consume(token::keyword_DO)) { return true; }
        if (parse_statement_sequence()) { return true; }
    }
    if (consume(token::keyword_END)) { return true; }
    return false;
}