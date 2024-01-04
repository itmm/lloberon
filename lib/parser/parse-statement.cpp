#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_statement() {
    if (token_.is(token::identifier)) {
        if (parse_assignment_or_procedure_call()) { return true; }
    } else if (token_.is(token::keyword_IF)) {
        if (parse_if_statement()) { return true; }
    } else if (token_.is(token::keyword_CASE)) {
        if (parse_case_statement()) { return true; }
    } else if (token_.is(token::keyword_WHILE)) {
        if (parse_while_statement()) { return true; }
    } else if (token_.is(token::keyword_REPEAT)) {
        if (parse_repeat_statement()) { return true; }
    } else if (token_.is(token::keyword_FOR)) {
        if (parse_for_statement()) { return true; }
    }
    return false;
}
