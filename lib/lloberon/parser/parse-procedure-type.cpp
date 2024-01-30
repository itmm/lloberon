#include "parser/parser.h"

type::Procedure_Ptr Parser::parse_procedure_type() {
	auto procedure_type { std::make_shared<type::Procedure>() };
	consume(token::keyword_PROCEDURE);
	parse_formal_parameters(*procedure_type);
	return procedure_type;
}