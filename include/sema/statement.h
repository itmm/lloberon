#pragma once

#include "context.h"
#include "stmt/statement.h"

namespace sema {
	class Statement {
	public:
		Statement() = default;

		std::shared_ptr<stmt::Statement> statement {
			std::make_shared<stmt::Statement>()
		};
	};
}