#include "parser/parser.h"

bool Parser::parse_label(sema::Label& label) {
    if (token_.is_one_of(token::integer_literal, token::string_literal)) {
        advance();
    } else {
        sema::Qual_Ident qual_ident { label.scope() };
        if (parse_qual_ident(qual_ident)) { return true; }
    }
    return false;
}