#include "parser/parser.h"

bool Parser::parse_qual_ident(sema::Qual_Ident& qual_ident) {
    qual_ident.clear();
    if (expect(token::identifier)) { return true; }
    auto decl = qual_ident.scope().lookup(token_.identifier().str());
    advance();

    if (! decl) { error(); return true; }
    auto module = llvm::dyn_cast<decl::Module>(&*decl);

    if (module) {
        if (token_.is(token::period)) {
            advance();
            if (expect(token::identifier)) { return true; }
            decl = module->lookup(token_.identifier().str());
            advance();
            if (! decl) { error(); return true; }
        } else { error(); return true; }
        qual_ident.module = std::static_pointer_cast<decl::Module>(decl);
    }
    qual_ident.declaration = decl;
    return false;
}