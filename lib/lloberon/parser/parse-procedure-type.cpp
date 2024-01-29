#include "parser/parser.h"

void Parser::parse_procedure_type(type::Type_Ptr& type) {
	auto procedure_type { std::make_shared<type::Procedure>() };
	consume(token::keyword_PROCEDURE);
	parse_formal_parameters(*procedure_type);
	type = procedure_type;
}