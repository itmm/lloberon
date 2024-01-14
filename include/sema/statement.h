#pragma once

#include "scope.h"
#include "stmt/statement.h"

namespace sema {
	class Statement {
	public:
		explicit Statement(Scope& scope) : scope { scope } { }

		Scope& scope;

		std::shared_ptr<stmt::Statement> statement {
			std::make_shared<stmt::Statement>()
		};
	};
}