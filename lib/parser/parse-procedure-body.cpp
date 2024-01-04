#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_procedure_body() {
    if (parse_declaration_sequence()) { return true; }
    if (token_.is(token::keyword_BEGIN)) {
        advance();
        Scope scope;
        sema::Statement_Sequence statement_sequence { scope };
        if (parse_statement_sequence(statement_sequence)) { return true; }
    }
    if (token_.is(token::keyword_RETURN)) {
        advance();
        Scope scope;
        sema::Expression expression { scope };
        if (parse_expression(expression)) { return true; }
    }
    if (consume(token::keyword_END)) { return true; }
    return false;
}