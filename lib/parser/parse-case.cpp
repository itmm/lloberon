#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_case() {
    if (token_.is_one_of(token::bar, token::keyword_END)) { error(); return true; }
    if (parse_case_list()) { return true; }
    if (consume(token::colon)) { return true; }
    if (parse_statement_sequence()) { return true; }
    return false;
}