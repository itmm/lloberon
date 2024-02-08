#include "llvm/IR/DerivedTypes.h"
#include "sema/context.h"
#include "type/procedure.h"

static type::Procedure_Ptr create_odd() {
	auto odd { std::make_shared<type::Procedure>() };
	odd->return_type = type::Type::base_integer;
	odd->parameters.emplace_back("x", type::Type::base_integer, false);
	odd->update_llvm_type();
	return odd;
}

type::Procedure_Ptr type::Procedure::procedure_odd { nullptr };

void type::Procedure::register_base_procedures(Scope& scope) {
	procedure_odd = create_odd();
	scope.insert("ODD", procedure_odd);
}

void type::Procedure::update_llvm_type() {
	std::vector<llvm::Type*> parameter_types { };
	for (const auto& item: parameters) {
		parameter_types.push_back(item.type->llvm_type);
	}
	llvm_type = llvm::FunctionType::get(
		return_type ? return_type->llvm_type : type::Type::ty_void->llvm_type,
		llvm::ArrayRef<llvm::Type*> { parameter_types }, false
	);
}
