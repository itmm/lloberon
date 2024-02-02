#include "parser/parser.h"
#include "type/array.h"
#include "type/pointer.h"
#include "expr/binary.h"
#include "expr/variable.h"
#include "expr/procedure.h"
#include "expr/unary.h"

expr::Expression_Ptr Parser::parse_designator() {
	auto qual_ident { parse_qual_ident() };

	std::shared_ptr<expr::Expression> expression;
	expression = expr::Variable::as_variable(qual_ident);

	while (
		expression && !std::dynamic_pointer_cast<type::Procedure>(
			expression->type
		)
	) {
		if (token::is(token::period)) {
			advance();
			expect(token::identifier);
			auto record_type { std::dynamic_pointer_cast<type::Record>(
				expression->type
			) };
			if (! record_type) { report(diag::err_record_expected); }
			bool found { false };
			for (const auto& entry : record_type->entries) {
				if (entry.name == token::value) {
					expression = expr::Binary::create(
						entry.type, token::period, expression,
						expr::Const::create(entry.name)
					);
					found = true;
					break;
				}
			}
			if (!found) { diag::report(diag::err_unknown_record_entry); }
			advance();
		} else if (token::is(token::left_bracket)) {
			advance();
			expr::Expression_List expression_list { parse_expression_list() };
			consume(token::right_bracket);
			for (auto count { expression_list.size() }; count; --count) {
				auto array_type { std::dynamic_pointer_cast<type::Array>(
					expression->type
				) };
				if (!array_type) { diag::report(diag::err_array_expected); }
				expression = std::make_shared<expr::Expression>(array_type->base);
			}
		} else if (token::is(token::ptr)) {
			auto pointer_type { std::dynamic_pointer_cast<type::Pointer>(
				expression->type)
			};
			if (!pointer_type) { diag::report(diag::err_pointer_expected); }
			expression = expr::Unary::create(
				pointer_type->points_to, token::ptr, expression
			);
			advance();
        } else if (token::is(token::left_parenthesis)) {
            advance();
            auto type { type::Type::as_type(parse_qual_ident()) };
			if (!type) { diag::report(diag::err_type_expected); }
            consume(token::right_parenthesis);
			expression = std::make_shared<expr::Expression>(type);
		} else { break; }
	}

	if (! expression) {
		auto procedure { expr::Procedure::as_procedure(qual_ident) };
		expression = procedure ? std::make_shared<expr::Expression>(procedure->type) : nullptr;
	}
	return expression;
}