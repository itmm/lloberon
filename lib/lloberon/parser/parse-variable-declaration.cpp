#include "parser/parser.h"
#include "expr/variable.h"

void Parser::parse_variable_declaration() {
	sema::Ident_List ident_list { parse_ident_list() };
	consume(token::colon);
	auto type { parse_type() };

	for (const auto& id: ident_list) {
		if (!context::scope->insert(
			id, std::make_shared<expr::Variable>(type)
		)) {
			diag::report(diag::err_already_defined);
		}
	}
}