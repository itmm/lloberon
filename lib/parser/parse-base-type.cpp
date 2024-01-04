#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_base_type() {
    if (parse_qual_ident()) { return true; }
    return false;
}