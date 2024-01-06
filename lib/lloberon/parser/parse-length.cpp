#include "parser/parser.h"

bool Parser::parse_length() {
    return parse_const_expression();
}