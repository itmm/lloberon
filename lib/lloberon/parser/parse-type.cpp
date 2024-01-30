#include "parser/parser.h"

void Parser::parse_type(type::Type_Ptr& type) {
	if (token::is(token::identifier)) {
		auto got { type::Type::as_type(parse_qual_ident()) };
		if (!got) { diag::report(diag::err_identifier_must_be_type); }
		type = got;
	} else if (token::is(token::keyword_ARRAY)) {
		type = parse_array_type();
	} else if (token::is(token::keyword_RECORD)) {
		type = parse_record_type();
	} else if (token::is(token::keyword_POINTER)) {
		type = parse_pointer_type();
	} else if (token::is(token::keyword_PROCEDURE)) {
		type = parse_procedure_type();
	} else {
		diag::report(diag::err_type_expected);
	}
}