#pragma once

#include "context.h"
#include "stmt/statement.h"

namespace sema {
	class Statement {
	public:
		explicit Statement(Context& context) : context { context } { }

		Context& context;

		std::shared_ptr<stmt::Statement> statement {
			std::make_shared<stmt::Statement>()
		};
	};
}