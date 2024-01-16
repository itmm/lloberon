#include "lexer/token.h"

namespace token {
	Kind kind;
	std::string value;
	llvm::SMLoc location;
}