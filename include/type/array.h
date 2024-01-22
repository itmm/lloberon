#pragma once

#include "type.h"

#include <memory>

namespace type {
	class Array : public Type {
	public:
		explicit Array(int count = 0, Type_Ptr base = nullptr) :
			count { count }, base { std::move(base) } { }

		int count;
		Type_Ptr base;
	};

	using Array_Ptr = std::shared_ptr<Array>;
}