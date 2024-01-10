#pragma once

#include "decl/declaration-with-scope.h"

namespace decl {
	class Procedure : public Declaration_With_Scope {
	public:
		Procedure(
			Declaration* enclosing_declaration,
			llvm::SMLoc loc, std::string name
		) : Declaration_With_Scope { } { }
	};
}