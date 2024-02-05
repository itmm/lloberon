#pragma once

#include "llvm/Support/SMLoc.h"

#include "sema/context.h"
#include "sema/scope.h"
#include "decl/declaration.h"

namespace decl {
	class Scope_Mixin {
	public:
		[[nodiscard]] decl::Declaration_Ptr lookup(const std::string& name) const {
			return scope->lookup(name);
		}

		bool insert(
			const std::string& name, const decl::Declaration_Ptr& declaration
		) {
			return scope->insert(name, declaration);
		}

		const Scope_Ptr scope { std::make_shared<Scope>(context::scope) };
		//const Scope_Ptr scope { std::make_shared<Scope>() };
	};
}