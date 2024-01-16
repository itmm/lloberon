#pragma once

#include "basic/token-kinds.h"

#include <string>

namespace token {
	extern Kind kind;
	extern std::string value;
	extern const char* source;

	[[nodiscard]] inline bool is(token::Kind knd) { return knd == kind; }

	[[nodiscard]] inline bool is_one_of(token::Kind knd) { return is(knd); }

	template<typename ...Args>
	[[nodiscard]] inline bool is_one_of(token::Kind first, Args... rest) {
		return is(first) || is_one_of(rest...);
	}
}
