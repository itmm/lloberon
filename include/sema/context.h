#pragma once

#include <memory>

#include "llvm/IR/LLVMContext.h"

#include "scope.h"

namespace context {
	extern llvm::LLVMContext context;
	extern std::shared_ptr<Scope> scope;

	inline void clear() {
		scope = std::make_shared<Scope>();
	}

	class Push_Scope {
		std::shared_ptr<Scope> old_;
	public:
		explicit Push_Scope(const std::shared_ptr<Scope>& new_scope):
			old_ { scope }
		{
			scope = new_scope;
		}
		~Push_Scope() { scope = old_; }
	};
}