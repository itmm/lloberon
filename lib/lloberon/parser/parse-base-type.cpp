#include "parser/parser.h"

bool Parser::parse_base_type(type::Record_Ptr& base_type) {
	sema::Qual_Ident ident;
	if (parse_qual_ident(ident)) { return true; }
	auto type { ident.as_type() };
	if (!type) { return report(diag::err_base_type_expected); }
	auto record { std::dynamic_pointer_cast<type::Record>(type) };
	if (!record) { return report(diag::err_base_type_must_be_record); }
	base_type->base = record;
	return false;
}