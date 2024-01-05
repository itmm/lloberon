#include "parser/parser.h"

bool Parser::parse() {
    Scope scope;
    Base_Type_Declaration::register_base_types(scope);

    return parse_module(scope);
}