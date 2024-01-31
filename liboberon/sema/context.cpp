#include "sema/context.h"

std::shared_ptr<Scope> context::scope { std::make_shared<Scope>() };

llvm::LLVMContext context::context;
