#include "parser/parser.h"

bool Parser::parse_import_list(Scope& scope) {
    Scope tmp(&scope, true);
    if (consume(token::keyword_IMPORT)) { return true; }
    if (parse_import(tmp)) { return true; }
    while (token_.is(token::comma)) {
        advance();
        if (parse_import(tmp)) { return true; }
    }
    if (consume(token::semicolon)) { return true; }
    scope.consume(tmp);
    return false;
}