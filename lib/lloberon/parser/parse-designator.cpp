#include "parser/parser.h"
#include "type/array.h"
#include "type/pointer.h"

bool Parser::parse_designator(sema::Designator& designator) {
	sema::Qual_Ident qual_ident { designator.context };
	if (parse_qual_ident(qual_ident)) { return true; }

	std::shared_ptr<expr::Expression> expression;
	expression = qual_ident.as_variable();

	while (expression && !std::dynamic_pointer_cast<type::Procedure>(expression->type)) {
		if (token_.is(token::period)) {
			advance();
			if (expect(token::identifier)) { return true; }
			auto record_type { std::dynamic_pointer_cast<type::Record>(
				expression->type
			) };
			if (! record_type) {
				diag().report(token_.location(), diag::err_record_expected);
				return true;
			}
			bool found { false };
			for (const auto& entry : record_type->entries) {
				if (entry.name == token_.identifier().str()) {
					expression = std::make_shared<expr::Expression>(entry.type);
					found = true;
					break;
				}
			}
			if (!found) {
				diag().report(
					token_.location(), diag::err_unknown_record_entry
				);
				return true;
			}
			advance();
		} else if (token_.is(token::left_bracket)) {
			advance();
			sema::Expression_List expression_list { designator.context };
			if (parse_expression_list(expression_list)) { return true; }
			if (consume(token::right_bracket)) { return true; }
			for (auto count { expression_list.list.size() }; count; --count) {
				auto array_type { std::dynamic_pointer_cast<type::Array>(
					expression->type
				) };
				if (!array_type) {
					diag().report(token_.location(), diag::err_array_expected);
					return true;
				}
				expression = std::make_shared<expr::Expression>(array_type->base);
			}
		} else if (token_.is(token::ptr)) {
			auto pointer_type { std::dynamic_pointer_cast<type::Pointer>(
				expression->type)
			};
			if (!pointer_type) {
				diag().report(token_.location(), diag::err_pointer_expected);
				return true;
			}
			expression = std::make_shared<expr::Expression>(
				pointer_type->points_to
			);
			advance();
        } else if (token_.is(token::left_parenthesis)) {
            advance();
            if (parse_qual_ident(qual_ident)) { return true; }
            if (consume(token::right_parenthesis)) { return true; }
			auto type { std::dynamic_pointer_cast<decl::Type>(qual_ident.declaration)};
			if (!type) {
				diag().report(token_.location(), diag::err_type_expected);
				return true;
			}
			expression = std::make_shared<expr::Expression>(type->type);
		} else { break; }
	}

	if (! expression) { expression = qual_ident.as_procedure(); }
	designator.expression = expression;

	return false;
}