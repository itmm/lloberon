#include "parser/parser.h"
#include "sema/scope.h"
#include "decl/module.h"

void Parser::parse_import(Scope& scope) {
	expect(token::identifier);
	auto name { token::value };
	auto full_name { name };
	advance();
	if (token::is(token::assign)) {
		advance();
		expect(token::identifier);
		full_name = token::value;
		advance();
	}
	auto module = decl::Module::get_module(full_name);
	if (!module) {
		diag::report(diag::err_module_not_found, name);
	}
	if (!scope.insert(name, module)) {
		diag::report(diag::err_import_already_used, name);
	}
}