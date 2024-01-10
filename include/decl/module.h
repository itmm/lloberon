#pragma once

#include "decl/declaration-with-scope.h"

namespace decl {
	class Module : public Declaration_With_Scope {
	public:
		explicit Module(std::string name) :
			Declaration_With_Scope { }, name_ { std::move(name) } { }

		[[nodiscard]] const std::string& name() const { return name_; }

	private:
		const std::string name_;
	};
}