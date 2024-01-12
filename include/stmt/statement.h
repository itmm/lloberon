#pragma once

#include <vector>

namespace stmt {
	class Statement {
	public:
		Statement() = default;
		virtual ~Statement() = default;
	};

	using Statement_Sequence = std::vector<std::shared_ptr<Statement>>;
}