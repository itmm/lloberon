#pragma once

#include "type.h"

namespace type {
	class Reference;

	using Reference_Ptr = std::shared_ptr<Reference>;

	class Reference : public Type {
	public:
		explicit Reference(Type_Ptr points_to) :
			points_to { std::move(points_to) } { }

		Type_Ptr points_to;
	};
}