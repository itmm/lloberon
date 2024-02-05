#include "sema/context.h"

Scope_Ptr context::scope { std::make_shared<Scope>() };

llvm::LLVMContext context::context;
