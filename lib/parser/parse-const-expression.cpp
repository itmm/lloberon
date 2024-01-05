#include "parser/parser.h"

bool Parser::parse_const_expression() {
    Scope scope;
    sema::Expression expression { scope };
    return parse_expression(expression);
}