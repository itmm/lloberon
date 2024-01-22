#include "parser/parser.h"
#include "sema/scope.h"

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
	auto module = std::make_shared<decl::Module>(full_name);
	if (!scope.insert(name, module)) {
		diag::report(diag::err_import_already_used, name);
	}
}