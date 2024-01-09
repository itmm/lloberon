#include "parser/parser.h"

bool Parser::parse_base_type(sema::Record_Type& base_type) {
    sema::Qual_Ident ident { base_type.scope() };
    if (parse_qual_ident(ident)) { return true; }
    auto type { std::dynamic_pointer_cast<decl::Type>(ident.declaration) };
    if (! type) { error(); return true; } // TODO: must be Record Type
    base_type.base_type = type->type;
    return false;
}