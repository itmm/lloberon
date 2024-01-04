#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_label() {
    if (token_.is_one_of(token::integer_literal, token::string_literal)) {
        advance();
    } else {
        Scope scope;
        Qual_Ident qual_ident { scope };
        if (parse_qual_ident(qual_ident)) { return true; }
    }
    return false;
}