#pragma once

#include "type.h"
#include "llvm/IR/DerivedTypes.h"

namespace type {
	class Reference;

	using Reference_Ptr = std::shared_ptr<Reference>;

	class Reference : public Type {
	public:
		explicit Reference(Type_Ptr points_to) :
 			Type { llvm::PointerType::get(points_to->llvm_type, 0) },
			points_to { std::move(points_to) } { }

		Type_Ptr points_to;
	};
}