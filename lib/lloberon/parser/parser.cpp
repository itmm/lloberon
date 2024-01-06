#include "parser/parser.h"
#include "decl/base-type.h"

bool Parser::parse() {
    Scope scope;
    decl::Base_Type::register_base_types(scope);

    return parse_module(scope);
}