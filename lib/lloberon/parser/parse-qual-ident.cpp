#include "parser/parser.h"

void Parser::parse_qual_ident(sema::Qual_Ident& qual_ident) {
	expect(token::identifier);
	auto decl = context::scope->lookup(token::value);
	advance();

	if (!decl) {
		diag::report(diag::err_identfier_expected);
	}
	auto module = std::dynamic_pointer_cast<decl::Module>(decl);

	if (module) {
		if (token::is(token::period)) {
			advance();
			expect(token::identifier);
			decl = module->lookup(token::value);
			advance();
			if (!decl) { diag::report(diag::err_module_identifier_expected); }
		} else { diag::report(diag::err_period_after_module_expected); }
		qual_ident.module = module;
	}
	qual_ident.declaration = decl;
}