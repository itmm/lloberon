#include "parser/parser.h"
#include "sema/scope.h"

void Parser::parse_module() {
	consume(token::keyword_MODULE);
	expect(token::identifier);
	auto module_name { token::value };
	advance();
	consume(token::semicolon);
	if (token::is(token::keyword_IMPORT)) {
		parse_import_list(*context::scope);
	}
	parse_declaration_sequence();
	if (token::is(token::keyword_BEGIN)) {
		advance();
		stmt::Statement_Sequence statement_sequence;
		parse_statement_sequence(statement_sequence);
	}
	consume(token::keyword_END);
	expect(token::identifier);
	if (module_name != token::value) {
		diag::report(
			diag::err_module_names_dont_match, module_name, token::value
		);
	}
	advance();
	consume(token::period);
	expect(token::eof);
}