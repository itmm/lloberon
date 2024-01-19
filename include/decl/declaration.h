#pragma once

#include <utility>
#include <string>

namespace decl {
	class Declaration {
	public:
		explicit Declaration() = default;

		virtual ~Declaration() = default;

		bool exported { false };
	};

	using Declaration_Ptr = std::shared_ptr<Declaration>;
}