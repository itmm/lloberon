#include "parser/parser.h"
#include "sema/scope.h"

bool Parser::parse_import(Scope& scope) {
    if (expect(token::identifier)) { return true; }
    auto name { token_.identifier().str() };
    auto full_name { name };
    advance();
    if (token_.is(token::assign)) {
        advance();
        if (expect(token::identifier)) { return true; }
        full_name = token_.identifier().str();
        advance();
    }
    auto module = std::make_shared<decl::Module>(full_name);
    if (!scope.insert(name, module)) { error(); return true; }
    return false;
}