#pragma once

#include "type.h"

#include "llvm/IR/DerivedTypes.h"

#include <memory>

namespace type {
	class Array : public Type {
	public:
		explicit Array(int count = 0, Type_Ptr base = nullptr) :
			Type { count && base && base->llvm_type ? llvm::ArrayType::get(base->llvm_type, count) : nullptr},
			count { count }, base { std::move(base) }
		{ }

		int count;
		Type_Ptr base;
	};

	using Array_Ptr = std::shared_ptr<Array>;
}