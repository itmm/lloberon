#include "sema/context.h"

Scope_Ptr context::scope { std::make_shared<Scope>() };

llvm::LLVMContext context::llvm_context;
llvm::TargetMachine *context::llvm_target_machine { nullptr };

llvm::LLVMContext& context::get_llvm_context() {
	return context::llvm_context;
}
