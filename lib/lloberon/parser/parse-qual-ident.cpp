#include "parser/parser.h"

bool Parser::parse_qual_ident(sema::Qual_Ident& qual_ident) {
	if (expect(token::identifier)) { return true; }
	auto decl = context::scope->lookup(token::value);
	advance();

	if (!decl) {
		return report(diag::err_identfier_expected);
	}
	auto module = std::dynamic_pointer_cast<decl::Module>(decl);

	if (module) {
		if (token::is(token::period)) {
			advance();
			if (expect(token::identifier)) { return true; }
			decl = module->lookup(token::value);
			advance();
			if (!decl) {
				return report(diag::err_module_identifier_expected);
			}
		} else {
			return report(diag::err_period_after_module_expected);
		}
		qual_ident.module = module;
	}
	qual_ident.declaration = decl;
	return false;
}