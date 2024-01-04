#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_repeat_statement() {
    if (consume(token::keyword_REPEAT)) { return true; }
    if (parse_statement_sequence()) { return true; }
    if (consume(token::keyword_UNTIL)) { return true; }
    if (parse_expression()) { return true; }
    return false;
}