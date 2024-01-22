#include "parser/parser.h"

void Parser::parse_base_type(type::Record_Ptr& base_type) {
	sema::Qual_Ident ident;
	parse_qual_ident(ident);
	auto type { ident.as_type() };
	if (!type) { diag::report(diag::err_base_type_expected); }
	auto record { std::dynamic_pointer_cast<type::Record>(type) };
	if (!record) { diag::report(diag::err_base_type_must_be_record); }
	base_type->base = record;
}