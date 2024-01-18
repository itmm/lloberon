#include "parser/parser.h"
#include "type/array.h"
#include "type/pointer.h"

bool Parser::parse_designator(expr::Expression_Ptr& designator) {
	sema::Qual_Ident qual_ident;
	if (parse_qual_ident(qual_ident)) { return true; }

	std::shared_ptr<expr::Expression> expression;
	expression = qual_ident.as_variable();

	while (
		expression && !std::dynamic_pointer_cast<type::Procedure>(
			expression->type
		)
	) {
		if (token::is(token::period)) {
			advance();
			if (expect(token::identifier)) { return true; }
			auto record_type { std::dynamic_pointer_cast<type::Record>(
				expression->type
			) };
			if (! record_type) { return report(diag::err_record_expected); }
			bool found { false };
			for (const auto& entry : record_type->entries) {
				if (entry.name == token::value) {
					expression = std::make_shared<expr::Expression>(entry.type);
					found = true;
					break;
				}
			}
			if (!found) { return report(diag::err_unknown_record_entry); }
			advance();
		} else if (token::is(token::left_bracket)) {
			advance();
			expr::Expression_List expression_list;
			if (parse_expression_list(expression_list)) { return true; }
			if (consume(token::right_bracket)) { return true; }
			for (auto count { expression_list.size() }; count; --count) {
				auto array_type { std::dynamic_pointer_cast<type::Array>(
					expression->type
				) };
				if (!array_type) { return report(diag::err_array_expected); }
				expression = std::make_shared<expr::Expression>(array_type->base);
			}
		} else if (token::is(token::ptr)) {
			auto pointer_type { std::dynamic_pointer_cast<type::Pointer>(
				expression->type)
			};
			if (!pointer_type) { return report(diag::err_pointer_expected); }
			expression = std::make_shared<expr::Expression>(
				pointer_type->points_to
			);
			advance();
        } else if (token::is(token::left_parenthesis)) {
            advance();
            if (parse_qual_ident(qual_ident)) { return true; }
            if (consume(token::right_parenthesis)) { return true; }
			auto type { std::dynamic_pointer_cast<decl::Type>(qual_ident.declaration)};
			if (!type) { return report(diag::err_type_expected); }
			expression = std::make_shared<expr::Expression>(type->type);
		} else { break; }
	}

	if (! expression) { expression = qual_ident.as_procedure(); }
	designator = expression;

	return false;
}