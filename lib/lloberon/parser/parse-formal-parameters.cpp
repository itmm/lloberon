#include "parser/parser.h"

bool Parser::parse_formal_parameters(type::Procedure_Ptr& procedure_type) {
	procedure_type = std::make_shared<type::Procedure>();
	if (consume(token::left_parenthesis)) { return true; }
	if (!token::is(token::right_parenthesis)) {
		if (parse_formal_parameter_section(procedure_type)) { return true; }
		while (token::is(token::semicolon)) {
			advance();
			if (parse_formal_parameter_section(procedure_type)) { return true; }
		}
	}
	if (consume(token::right_parenthesis)) { return true; }
	if (token::is(token::colon)) {
		advance();
		sema::Qual_Ident qual_ident;
		if (parse_qual_ident(qual_ident)) { return true; }
		auto return_type { qual_ident.as_type() };

		if (! return_type) { return report(diag::err_type_expected); }
		procedure_type->return_type = return_type;
	}
	return false;
}