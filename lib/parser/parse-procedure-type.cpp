#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_procedure_type() {
    if (consume(token::keyword_PROCEDURE)) { return true; }
    if (parse_formal_parameters()) { return true; }
    return false;
}