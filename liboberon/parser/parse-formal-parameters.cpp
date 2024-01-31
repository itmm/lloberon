#include "parser/parser.h"

void Parser::parse_formal_parameters(type::Procedure& procedure_type) {
	consume(token::left_parenthesis);
	if (!token::is(token::right_parenthesis)) {
		parse_formal_parameter_section(procedure_type);
		while (token::is(token::semicolon)) {
			advance();
			parse_formal_parameter_section(procedure_type);
		}
	}
	consume(token::right_parenthesis);
	if (token::is(token::colon)) {
		advance();
		auto return_type { type::Type::as_type(parse_qual_ident()) };

		if (! return_type) { diag::report(diag::err_type_expected); }
		procedure_type.return_type = return_type;
	}
}