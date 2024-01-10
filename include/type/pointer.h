#pragma once

#include "record.h"

#include <memory>

namespace type {
	class Pointer : public Type {
	public:
		explicit Pointer(std::shared_ptr<Record> points_to) :
			points_to { std::move(points_to) } { }

		std::shared_ptr<Record> points_to;
	};
}