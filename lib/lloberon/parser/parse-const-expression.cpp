#include "parser/parser.h"

bool Parser::parse_const_expression(sema::Const_Expression& const_expression) {
    const_expression.clear();
    sema::Expression expression { const_expression.scope() };
    if (parse_expression(expression)) { return true; }
    auto const_value { std::dynamic_pointer_cast<expr::Const>(expression.expression) };
    if (! const_value) { error(); return true; }
    const_expression.expression = const_value;
    return false;
}