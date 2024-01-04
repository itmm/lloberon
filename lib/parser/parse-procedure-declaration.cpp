#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_procedure_declaration() {
    if (parse_procedure_heading()) { return true; }
    if (consume(token::semicolon)) { return true; }
    if (parse_procedure_body()) { return true; }
    if (expect(token::identifier)) { return true; }
    advance();
    return false;
}