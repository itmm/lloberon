#include "parser/parser.h"

bool Parser::parse_expression_list(sema::Expression_List& expression_list) {
    sema::Expression expression { expression_list.scope() };
    if (parse_expression(expression)) { return true; }
    while (token_.is(token::comma)) {
        advance();
        if (parse_expression(expression)) { return true; }
    }
    return false;
}