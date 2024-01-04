#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_case_statement() {
    if (consume(token::keyword_CASE)) { return true; }
    Scope scope;
    sema::Expression expression { scope };
    if (parse_expression(expression)) { return true; }
    if (consume(token::keyword_OF)) { return true; }
    sema::Case case_arg { scope };
    if (parse_case(case_arg)) { return true; }
    while (token_.is(token::bar)) {
        advance();
        if (parse_case(case_arg)) { return true; }
    }
    if (consume(token::keyword_END)) { return true; }
    return false;
}