#include <vector>

#include "parser/parser.h"
#include "type/array.h"

type::Array_Ptr Parser::parse_array_type() {
	std::vector<int> counts;
	consume(token::keyword_ARRAY);
	int length { parse_length() };
	counts.push_back(length);
	while (token::is(token::comma)) {
		advance();
		length = parse_length();
		counts.push_back(length);
	}
	consume(token::keyword_OF);
	auto base { parse_type() };
	type::Array_Ptr current {
		std::make_shared<type::Array>(counts.back(), base)
	};
	for (auto i { counts.size() }; i > 1; --i) {
		current = std::make_shared<type::Array>(counts[i - 2], current);
	}
	return current;
}