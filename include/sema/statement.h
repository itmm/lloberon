#pragma once

#include "scope.h"
#include "stmt/statement.h"

namespace sema {
	class Statement {
	public:
		explicit Statement(Scope& scope) : scope_ { scope } { }

		Scope& scope() { return scope_; }

		void clear() {
			statement = std::make_shared<stmt::Statement>();
		}

		std::shared_ptr<stmt::Statement> statement {
			std::make_shared<stmt::Statement>()
		};

	private:
		Scope& scope_;
	};
}