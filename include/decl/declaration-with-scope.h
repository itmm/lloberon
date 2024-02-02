#pragma once

#include "llvm/Support/SMLoc.h"

#include "sema/scope.h"
#include "decl/declaration.h"

namespace decl {
	class Scope_Mixin {
	public:
		std::shared_ptr<decl::Declaration> lookup(const std::string& name) {
			return scope_.lookup(name);
		}

		bool insert(
			const std::string& name,
			const std::shared_ptr<decl::Declaration>& declaration
		) {
			return scope_.insert(name, declaration);
		}

	private:
		Scope scope_;
	};
}