#include "parser/parser.h"

bool Parser::parse_formal_parameter_section(
	sema::Procedure_Type& procedure_type
) {
	bool reference { false };
	if (token::is(token::keyword_VAR)) { reference = true; advance(); }
	std::vector<std::string> names;
	if (expect(token::identifier)) { return true; }
	names.push_back(token::value);
	advance();
	while (token::is(token::comma)) {
		advance();
		if (expect(token::identifier)) { return true; }
		names.push_back(token::value);
		advance();
	}

	std::map<std::string, int> counts;
	for (const auto& name: names) {
		counts[name] += 1;
	}
	for (const auto& param: procedure_type.procedure->parameters) {
		counts[param.name] += 1;
	}
	for (const auto& entry: counts) {
		if (entry.second > 1) {
			return report(diag::err_already_defined, entry.first);
		}
	}

	if (consume(token::colon)) { return true; }
	sema::Type formal_type { procedure_type.context };
	if (parse_formal_type(formal_type)) { return true; }

	for (const auto& name : names) {
		procedure_type.procedure->parameters.emplace_back(
			name, formal_type.type, reference
		);
	}

	return false;
}