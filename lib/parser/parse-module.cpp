#include "lloberon/parser/parser.h"
#include "lloberon/sema/declaration.h"
#include "lloberon/sema/scope.h"

using namespace lloberon;

bool Parser::parse_module(Scope& scope) {
    if (consume(token::keyword_MODULE)) { return true; }
    if (expect(token::identifier)) { return true; }
    auto module_name { token_.identifier() };
    advance();
    if (consume(token::semicolon)) { return true; }
    if (token_.is(token::keyword_IMPORT)) {
        if (parse_import_list(scope)) { return true; }
    }
    sema::Declaration_Sequence declaration_sequence { scope };
    if (parse_declaration_sequence(declaration_sequence)) { return true; }
    if (token_.is(token::keyword_BEGIN)) {
        advance();
        sema::Statement_Sequence statement_sequence { scope };
        if (parse_statement_sequence(statement_sequence)) { return true; }
    }
    if (consume(token::keyword_END)) { return true; }
    if (expect(token::identifier)) { return true; }
    if (module_name != token_.identifier()) { error(); return true; }
    advance();
    if (consume(token::period)) { return true; }
    if (expect(token::eof)) { return true; }
    return false;
}