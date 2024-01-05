#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_for_statement(sema::For_Statement& for_statement) {
    if (consume(token::keyword_FOR)) { return true; }
    if (expect(token::identifier)) { return true; }
    advance();
    if (consume(token::assign)) { return true; }
    sema::Expression expression { for_statement.scope() };
    if (parse_expression(expression)) { return true; }
    if (consume(token::keyword_TO)) { return true; }
    if (parse_expression(expression)) { return true; }
    if (token_.is(token::keyword_BY)) {
        advance();
        if (parse_const_expression()) { return true; }
    }
    if (consume(token::keyword_DO)) { return true; }
    sema::Statement_Sequence statement_sequence { for_statement.scope() };
    if (parse_statement_sequence(statement_sequence)) { return true; }
    if (consume(token::keyword_END)) { return true; }
    return false;
}