#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_base_type(Base_Type& base_type) {
    Qual_Ident ident { base_type.scope() };
    if (parse_qual_ident(ident)) { return true; }
    return false;
}