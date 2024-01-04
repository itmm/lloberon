#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_assignment_or_procedure_call() {
    if (parse_designator()) { return true; }
    if (token_.is(token::assign)) {
        advance();
        if (parse_expression()) { return true; }
    } else {
        if (token_.is(token::left_parenthesis)) {
            if (parse_actual_parameters()) { return true; }
        }
    }
    return false;
}