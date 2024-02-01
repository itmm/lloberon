#pragma once

#include "decl/declaration-with-scope.h"

namespace decl {
	class Module;

	using Module_Ptr = std::shared_ptr<Module>;

	class Module : public Declaration_With_Scope {
	public:
		explicit Module(std::string name) :
			Declaration_With_Scope { }, name_ { std::move(name) } { }

		[[nodiscard]] const std::string& name() const { return name_; }

		static Module_Ptr system_module;
		static Module_Ptr out_module;

		static void init_internal_modules();
		static Module_Ptr get_module(const std::string& name);

	private:
		const std::string name_;
	};
}