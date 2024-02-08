#pragma once

#include <memory>

#include "llvm/IR/Type.h"
#include "decl/declaration.h"

namespace type {
	class Type;

	using Type_Ptr = std::shared_ptr<Type>;

	class Type: public decl::Declaration {
	public:
		explicit Type(llvm::Type* llvm_type): llvm_type { llvm_type } { }

		llvm::Type* llvm_type;

		bool is_bool();

		bool is_numeric();

		bool is_integer();

		static Type_Ptr base_boolean;

		static Type_Ptr base_char;

		static Type_Ptr base_integer;

		static Type_Ptr base_real;

		static Type_Ptr base_byte;

		static Type_Ptr base_set;

		static Type_Ptr as_type(const decl::Declaration_Ptr& declaration) {
			return std::dynamic_pointer_cast<Type>(declaration);
		}
	};
}