#include "parser/parser.h"

type::Record_Ptr Parser::parse_base_type() {
	auto type { type::Type::as_type(parse_qual_ident()) };
	if (!type) { diag::report(diag::err_base_type_expected); }
	auto record { std::dynamic_pointer_cast<type::Record>(type) };
	if (!record) { diag::report(diag::err_base_type_must_be_record); }
	return record;
}