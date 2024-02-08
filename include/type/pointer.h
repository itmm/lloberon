#pragma once

#include "record.h"

#include <memory>
#include "llvm/IR/DerivedTypes.h"

namespace type {
	class Pointer;

	using Pointer_Ptr = std::shared_ptr<Pointer>;

	class Pointer : public Type {
	public:
		explicit Pointer(Record_Ptr points_to) :
 			Type { points_to && points_to->llvm_type ? llvm::PointerType::get(points_to->llvm_type, 0) : nullptr },
			points_to { std::move(points_to) } { }

		Record_Ptr points_to;

		static Pointer_Ptr pointer_to_nil;
	};
}