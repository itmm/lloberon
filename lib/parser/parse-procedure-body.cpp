#include "parser/parser.h"

using namespace lloberon;

bool Parser::parse_procedure_body(sema::Procedure_Body& procedure_body) {
    sema::Declaration_Sequence declaration_sequence { procedure_body.scope() };
    if (parse_declaration_sequence(declaration_sequence)) { return true; }
    if (token_.is(token::keyword_BEGIN)) {
        advance();
        sema::Statement_Sequence statement_sequence { procedure_body.scope() };
        if (parse_statement_sequence(statement_sequence)) { return true; }
    }
    if (token_.is(token::keyword_RETURN)) {
        advance();
        sema::Expression expression { procedure_body.scope() };
        if (parse_expression(expression)) { return true; }
    }
    if (consume(token::keyword_END)) { return true; }
    return false;
}