#include "parser/parser.h"
#include "expr/integer.h"

bool Parser::parse_length(sema::Length& length) {
    length.clear();
    sema::Const_Expression expression { length.scope() };
    if (parse_const_expression(expression)) { return true; }
    auto value { std::dynamic_pointer_cast<expr::Integer>(expression.expression) };
    if (!value || value->value < 0) { error(); return true; }
    length.length = value->value;
    return false;
}