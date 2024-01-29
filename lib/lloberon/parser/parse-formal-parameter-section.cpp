#include "parser/parser.h"

void Parser::parse_formal_parameter_section(
	type::Procedure& procedure_type
) {
	bool reference { false };
	if (token::is(token::keyword_VAR)) { reference = true; advance(); }
	std::vector<std::string> names;
	expect(token::identifier);
	names.push_back(token::value);
	advance();
	while (token::is(token::comma)) {
		advance();
		expect(token::identifier);
		names.push_back(token::value);
		advance();
	}

	consume(token::colon);
	type::Type_Ptr formal_type { parse_formal_type() };

	for (const auto& name : names) {
		procedure_type.parameters.emplace_back(
			name, formal_type, reference
		);
	}
}