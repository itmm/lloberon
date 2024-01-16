#pragma once

#include "basic/token-kinds.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/SMLoc.h"

#include <cstddef>

namespace token {
	extern Kind kind;
	extern std::string value;
	extern llvm::SMLoc location;

	[[nodiscard]] inline bool is(token::Kind knd) { return knd == kind; }

	[[nodiscard]] inline bool is_one_of(token::Kind knd) { return is(knd); }

	template<typename ...Args>
	[[nodiscard]] inline bool is_one_of(token::Kind first, Args... rest) {
		return is(first) || is_one_of(rest...);
	}

}

class Token {
public:
	[[nodiscard]] size_t length() const { return token::value.length(); }

	[[nodiscard]] llvm::SMLoc location() const { return token::location; }

	[[nodiscard]] const std::string& identifier() const { return token::value; }

	const std::string& literal_data() { return token::value; }
};