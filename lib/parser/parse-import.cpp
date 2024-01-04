#include "lloberon/parser/parser.h"
#include "lloberon/ast/declaration.h"
#include "lloberon/sema/scope.h"

using namespace lloberon;

bool Parser::parse_import(Scope& scope) {
    if (expect(token::identifier)) { return true; }
    auto loc { token_.location() };
    auto name { token_.identifier().str() };
    auto full_name { name };
    advance();
    if (token_.is(token::assign)) {
        advance();
        if (expect(token::identifier)) { return true; }
        full_name = token_.identifier().str();
        advance();
    }
    auto module = new Module_Declaration(loc, name, full_name);
    if (!scope.insert(module)) { error(); return true; }
    return false;
}