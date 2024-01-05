#include "parser/parser.h"

using namespace lloberon;

bool Parser::parse_length() {
    return parse_const_expression();
}