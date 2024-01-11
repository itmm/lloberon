#pragma once

#include "scope.h"
#include "type/procedure.h"

namespace sema {
	class Procedure_Type {
	public:
		explicit Procedure_Type(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() {
			procedure = std::make_shared<type::Procedure>();
		}

		std::shared_ptr<type::Procedure> procedure {
			std::make_shared<type::Procedure>()
		};

	private:
		Scope& scope_;
	};
}