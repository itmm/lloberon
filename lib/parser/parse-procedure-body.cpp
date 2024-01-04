#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_procedure_body() {
    if (parse_declaration_sequence()) { return true; }
    if (token_.is(token::keyword_BEGIN)) {
        advance();
        if (parse_statement_sequence()) { return true; }
    }
    if (token_.is(token::keyword_RETURN)) {
        advance();
        if (parse_expression()) { return true; }
    }
    if (consume(token::keyword_END)) { return true; }
    return false;
}