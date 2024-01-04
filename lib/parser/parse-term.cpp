#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_term(Term& term) {
    Factor factor { term.scope() };
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