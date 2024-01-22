#include "parser/parser.h"

void Parser::parse_formal_parameters(type::Procedure_Ptr& procedure_type) {
	procedure_type = std::make_shared<type::Procedure>();
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
		sema::Qual_Ident qual_ident;
		parse_qual_ident(qual_ident);
		auto return_type { qual_ident.as_type() };

		if (! return_type) { diag::report(diag::err_type_expected); }
		procedure_type->return_type = return_type;
	}
}