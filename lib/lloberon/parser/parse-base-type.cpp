#include "parser/parser.h"

bool Parser::parse_base_type(sema::Record_Type& base_type) {
	sema::Qual_Ident ident { base_type.context };
	if (parse_qual_ident(ident)) { return true; }
	auto type { std::dynamic_pointer_cast<decl::Type>(ident.declaration) };
	if (!type) { return report(diag::err_base_type_expected); }
	auto record { std::dynamic_pointer_cast<type::Record>(type->type) };
	if (!record) { return report(diag::err_base_type_must_be_record); }
	base_type.record->base = record;
	return false;
}