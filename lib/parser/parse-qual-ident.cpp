#include "parser/parser.h"

bool Parser::parse_qual_ident(lloberon::sema::Qual_Ident& qual_ident) {
    qual_ident.clear();
    if (expect(token::identifier)) { return true; }
    Declaration* decl = qual_ident.scope().lookup(token_.identifier().str());
    advance();

    if (decl == nullptr) { error(); return true; }
    auto module = llvm::dyn_cast<Module_Declaration>(decl);

    if (module) {
        if (token_.is(token::period)) {
            advance();
            if (expect(token::identifier)) { return true; }
            decl = module->lookup(token_.identifier().str());
            advance();
            if (! decl) { error(); return true; }
        } else { error(); return true; }
    }
    qual_ident.declaration = decl;
    qual_ident.module = module;
    return false;
}