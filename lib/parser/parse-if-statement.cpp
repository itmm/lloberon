#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_if_statement() {
    if (consume(token::keyword_IF)) { return true; }
    Scope scope;
    sema::Expression expression { scope };
    if (parse_expression(expression)) { return true; }
    if(consume(token::keyword_THEN)) { return true; }
    sema::Statement_Sequence statement_sequence { scope };
    if (parse_statement_sequence(statement_sequence)) { return true; }
    while (token_.is(token::keyword_ELSIF)) {
        advance();
        if (parse_expression(expression)) { return true; }
        if (consume(token::keyword_THEN)) { return true; }
        if (parse_statement_sequence(statement_sequence)) { return true; }
    }
    if (token_.is(token::keyword_ELSE)) {
        advance();
        if (parse_statement_sequence(statement_sequence)) { return true; }
    }
    if (consume(token::keyword_END)) { return true; }
    return false;
}