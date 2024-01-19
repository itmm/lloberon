#include "parser/parser.h"
#include "sema/scope.h"

bool Parser::parse_module() {
	if (consume(token::keyword_MODULE)) { return true; }
	if (expect(token::identifier)) { return true; }
	auto module_name { token::value };
	advance();
	if (consume(token::semicolon)) { return true; }
	if (token::is(token::keyword_IMPORT)) {
		if (parse_import_list(*context::scope)) { return true; }
	}
	if (parse_declaration_sequence()) { return true; }
	if (token::is(token::keyword_BEGIN)) {
		advance();
		stmt::Statement_Sequence statement_sequence;
		if (parse_statement_sequence(statement_sequence)) { return true; }
	}
	if (consume(token::keyword_END)) { return true; }
	if (expect(token::identifier)) { return true; }
	if (module_name != token::value) {
		return report(
			diag::err_module_names_dont_match, module_name, token::value
		);
	}
	advance();
	if (consume(token::period)) { return true; }
	if (expect(token::eof)) { return true; }
	return false;
}