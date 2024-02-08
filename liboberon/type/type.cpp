#include "type/type.h"
#include "llvm/IR/DerivedTypes.h"
#include "sema/context.h"

type::Type_Ptr type::Type::base_boolean {
	std::make_shared<Type>(llvm::Type::getInt1Ty(context::get_llvm_context()))
};

type::Type_Ptr type::Type::base_char {
	std::make_shared<Type>(llvm::Type::getInt8Ty(context::get_llvm_context()))
};

type::Type_Ptr type::Type::base_integer {
	std::make_shared<Type>(llvm::Type::getInt32Ty(context::get_llvm_context()))
};

type::Type_Ptr type::Type::base_real {
	std::make_shared<Type>(llvm::Type::getDoubleTy(context::get_llvm_context()))
};

type::Type_Ptr type::Type::base_byte {
	std::make_shared<Type>(llvm::Type::getInt8Ty(context::get_llvm_context()))
};

type::Type_Ptr type::Type::base_set {
	std::make_shared<Type>(llvm::Type::getInt32Ty(context::get_llvm_context()))
};

bool type::Type::is_bool() {
	return this == &*type::Type::base_boolean;
}

bool type::Type::is_numeric() {
	return is_integer() || this == &*base_real;
}

bool type::Type::is_integer() {
	return this == &*base_integer || this == &*base_byte;
}