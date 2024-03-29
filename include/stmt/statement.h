#pragma once

#include <vector>

namespace stmt {
	class Statement {
	public:
		Statement() = default;
		virtual ~Statement() = default;
	};

	using Statement_Ptr = std::shared_ptr<Statement>;

	using Statement_Sequence = std::vector<Statement_Ptr>;
}