#pragma once

#include <memory>

#include "llvm/IR/LLVMContext.h"
#include "llvm/MC/TargetRegistry.h"

#include "scope.h"

namespace context {
	extern llvm::LLVMContext llvm_context;
	extern llvm::TargetMachine *llvm_target_machine;
	extern llvm::Module* llvm_current_module;
	extern llvm::Function* llvm_current_function;

	extern Scope_Ptr scope;

	llvm::LLVMContext& get_llvm_context();

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