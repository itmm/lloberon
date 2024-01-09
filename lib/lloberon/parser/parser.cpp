#include "parser/parser.h"
#include "decl/type.h"

bool Parser::parse() {
    Scope scope;
    decl::Type::register_base_types(scope);

    return parse_module(scope);
}