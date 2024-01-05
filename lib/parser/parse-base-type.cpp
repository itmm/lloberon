#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_base_type(sema::Base_Type& base_type) {
    sema::Qual_Ident ident { base_type.scope() };
    if (parse_qual_ident(ident)) { return true; }
    return false;
}