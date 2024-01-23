#include "parser/parser.h"
#include "decl/module.h"

decl::Declaration_Ptr Parser::parse_qual_ident() {
	expect(token::identifier);
	auto decl = context::scope->lookup(token::value);
	if (!decl) {
		diag::report(diag::err_identfier_expected);
	}
	advance();

	auto module = std::dynamic_pointer_cast<decl::Module>(decl);
	if (module) {
		if (token::is(token::period)) {
			advance();
			expect(token::identifier);
			decl = module->lookup(token::value);
			if (!decl) { diag::report(diag::err_module_identifier_expected); }
			advance();
		} else { diag::report(diag::err_period_after_module_expected); }
	}
	return decl;
}