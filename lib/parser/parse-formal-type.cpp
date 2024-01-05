#include "parser/parser.h"

using namespace lloberon;

bool Parser::parse_formal_type(sema::Formal_Type& formal_type) {
    while (token_.is(token::keyword_ARRAY)) {
        advance();
        if (consume(token::keyword_OF)) { return true; }
    }
    sema::Qual_Ident qual_ident { formal_type.scope() };
    if (parse_qual_ident(qual_ident)) { return true; }
    return false;
}