#include "parser/parser.h"

using namespace lloberon;

bool Parser::parse_case_statement(sema::Case_Statement& case_statement) {
    if (consume(token::keyword_CASE)) { return true; }
    sema::Expression expression { case_statement.scope() };
    if (parse_expression(expression)) { return true; }
    if (consume(token::keyword_OF)) { return true; }
    sema::Case case_arg { case_statement.scope() };
    if (parse_case(case_arg)) { return true; }
    while (token_.is(token::bar)) {
        advance();
        if (parse_case(case_arg)) { return true; }
    }
    if (consume(token::keyword_END)) { return true; }
    return false;
}