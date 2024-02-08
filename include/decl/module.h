#pragma once

#include "llvm/IR/Module.h"

#include "decl/declaration-with-scope.h"

namespace decl {
	class Module;

	using Module_Ptr = std::shared_ptr<Module>;

	class Module : public Declaration, public Scope_Mixin {
	public:
		explicit Module(std::string name) : Declaration { },
			llvm_module { std::make_unique<llvm::Module>(
				name, context::llvm_context
			) }, name_ { std::move(name) }
		{ }

		std::unique_ptr<llvm::Module> llvm_module;

		[[nodiscard]] const std::string& name() const { return name_; }

		static Module_Ptr system_module;
		static Module_Ptr out_module;

		static void init_internal_modules();
		static Module_Ptr get_module(const std::string& name);

	private:
		const std::string name_;
	};
}