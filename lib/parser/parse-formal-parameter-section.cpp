#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_formal_parameter_section(Formal_Parameter_Section& formal_parameter_section) {
    if (token_.is(token::keyword_VAR)) { advance(); }
    if (consume(token::identifier)) { return true; }
    while (token_.is(token::comma)) {
        advance();
        if (consume(token::identifier)) { return true; }
    }
    if (consume(token::colon)) { return true; }
    lloberon::Formal_Type formal_type { formal_parameter_section.scope() };
    if (parse_formal_type(formal_type)) { return true; }
    return false;
}