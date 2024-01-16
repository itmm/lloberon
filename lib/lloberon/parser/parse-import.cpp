#include "parser/parser.h"
#include "sema/scope.h"

bool Parser::parse_import(Scope& scope) {
	if (expect(token::identifier)) { return true; }
	auto name { token_.identifier() };
	auto full_name { name };
	advance();
	if (token::is(token::assign)) {
		advance();
		if (expect(token::identifier)) { return true; }
		full_name = token_.identifier();
		advance();
	}
	auto module = std::make_shared<decl::Module>(full_name);
	if (!scope.insert(name, module)) {
		diag().report(token_.location(), diag::err_import_already_used, name);
		return true;
	}
	return false;
}