#pragma once

#include "scope.h"
#include "decl/module.h"

namespace sema {
	class Qual_Ident {
	public:
		explicit Qual_Ident(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() {
			declaration = nullptr;
			module = nullptr;
		}

		std::shared_ptr<decl::Declaration> declaration { nullptr };
		std::shared_ptr<decl::Module> module { nullptr };
	private:
		Scope& scope_;
	};
}