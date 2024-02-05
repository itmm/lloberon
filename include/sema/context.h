#pragma once

#include <memory>

#include "llvm/IR/LLVMContext.h"

#include "scope.h"

namespace context {
	extern llvm::LLVMContext context;
	extern Scope_Ptr scope;

	inline void clear() { scope = std::make_shared<Scope>(); }

	class Push_Scope {
		Scope_Ptr old_;
	public:
		explicit Push_Scope(const Scope_Ptr& new_scope): old_ { scope }
		{
			scope = new_scope;
		}
		~Push_Scope() { scope = old_; }
	};
}