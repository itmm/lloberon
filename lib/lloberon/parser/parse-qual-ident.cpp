#include "parser/parser.h"

bool Parser::parse_qual_ident(sema::Qual_Ident& qual_ident) {
	qual_ident.clear();
	if (expect(token::identifier)) { return true; }
	auto decl = qual_ident.scope().lookup(token_.identifier().str());
	advance();

	if (!decl) {
		diag().report(token_.location(), diag::err_identfier_expected);
		return true;
	}
	auto module = std::dynamic_pointer_cast<decl::Module>(decl);

	if (module) {
		if (token_.is(token::period)) {
			advance();
			if (expect(token::identifier)) { return true; }
			decl = module->lookup(token_.identifier().str());
			advance();
			if (!decl) {
				diag().report(
					token_.location(), diag::err_module_identifier_expected
				);
				return true;
			}
		} else {
			diag().report(
				token_.location(), diag::err_period_after_module_expected
			);
			return true;
		}
		qual_ident.module = module;
	}
	qual_ident.declaration = decl;
	return false;
}