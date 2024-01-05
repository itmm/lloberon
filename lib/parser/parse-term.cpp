#include "parser/parser.h"

bool Parser::parse_term(lloberon::sema::Term& term) {
    lloberon::sema::Factor factor { term.scope() };
    if (parse_factor(factor)) { return true; }
    while (token_.is_one_of(
        token::star, token::slash, token::keyword_DIV,
        token::keyword_MOD, token::andop
    )) {
        advance();
        if (parse_factor(factor)) { return true; }
    }
    return false;
}