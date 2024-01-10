#include "parser/parser.h"

bool Parser::parse_length(sema::Const_Expression& expression) {
    return parse_const_expression(expression);
}