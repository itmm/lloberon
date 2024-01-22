#include "parser/parser.h"

void Parser::parse_type(type::Type_Ptr& type) {
	if (token::is(token::identifier)) {
		sema::Qual_Ident qual_ident;
		parse_qual_ident(qual_ident);
		auto got { qual_ident.as_type() };
		if (!got) { diag::report(diag::err_identifier_must_be_type); }
		type = got;
	} else if (token::is(token::keyword_ARRAY)) {
		parse_array_type(type);
	} else if (token::is(token::keyword_RECORD)) {
		parse_record_type(type);
	} else if (token::is(token::keyword_POINTER)) {
		parse_pointer_type(type);
	} else if (token::is(token::keyword_PROCEDURE)) {
		parse_procedure_type(type);
	} else {
		diag::report(diag::err_type_expected);
	}
}