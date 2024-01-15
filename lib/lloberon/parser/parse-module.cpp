#include "parser/parser.h"
#include "sema/scope.h"

bool Parser::parse_module(Context& context) {
	if (consume(token::keyword_MODULE)) { return true; }
	if (expect(token::identifier)) { return true; }
	auto module_name { token_.identifier() };
	advance();
	if (consume(token::semicolon)) { return true; }
	if (token_.is(token::keyword_IMPORT)) {
		if (parse_import_list(*context.scope)) { return true; }
	}
	if (parse_declaration_sequence(context)) { return true; }
	if (token_.is(token::keyword_BEGIN)) {
		advance();
		sema::Statement_Sequence statement_sequence { context };
		if (parse_statement_sequence(statement_sequence)) { return true; }
	}
	if (consume(token::keyword_END)) { return true; }
	if (expect(token::identifier)) { return true; }
	if (module_name != token_.identifier()) {
		diag().report(
			token_.location(), diag::err_module_names_dont_match,
			module_name, token_.identifier()
		);
		return true;
	}
	advance();
	if (consume(token::period)) { return true; }
	if (expect(token::eof)) { return true; }
	return false;
}