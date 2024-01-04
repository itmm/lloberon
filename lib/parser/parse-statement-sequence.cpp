#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_statement_sequence(sema::Statement_Sequence& statement_sequence) {
    sema::Statement statement { statement_sequence.scope() };
    if (parse_statement(statement)) { return true; }
    while (token_.is(token::semicolon)) {
        advance();
        if (parse_statement(statement)) { return true; }
    }
    return false;
}