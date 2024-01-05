#include "parser/parser.h"

using namespace lloberon;

bool Parser::parse_const_expression() {
    Scope scope;
    sema::Expression expression { scope };
    return parse_expression(expression);
}