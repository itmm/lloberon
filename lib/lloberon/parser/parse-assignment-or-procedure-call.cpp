#include "parser/parser.h"

bool Parser::parse_assignment_or_procedure_call(
    sema::Assignment_Or_Procedure_Call& assignment_or_procedure_call
) {
    sema::Designator designator { assignment_or_procedure_call.scope() };
    if (parse_designator(designator)) { return true; }
    if (token_.is(token::assign)) {
        advance();
        sema::Expression expression { assignment_or_procedure_call.scope() };
        if (parse_expression(expression)) { return true; }
    } else {
        if (token_.is(token::left_parenthesis)) {
            sema::Actual_Parameters actual_parameters { assignment_or_procedure_call.scope() };
            if (parse_actual_parameters(actual_parameters)) { return true; }
        }
    }
    return false;
}