#include "parser/parser.h"

bool Parser::parse_repeat_statement(sema::Repeat_Statement& repeat_statement) {
    if (consume(token::keyword_REPEAT)) { return true; }
    sema::Statement_Sequence statement_sequence { repeat_statement.scope() };
    if (parse_statement_sequence(statement_sequence)) { return true; }
    if (consume(token::keyword_UNTIL)) { return true; }
    sema::Expression expression { repeat_statement.scope() };
    if (parse_expression(expression)) { return true; }
    return false;
}