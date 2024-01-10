#pragma once

#include "type.h"

#include <memory>

namespace type {
	class Array : public Type {
	public:
		explicit Array(int count = 0, std::shared_ptr<Type> base = nullptr) :
			count { count }, base { std::move(base) } { }

		int count;
		std::shared_ptr<Type> base;
	};
}