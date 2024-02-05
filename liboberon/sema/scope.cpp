#include "sema/scope.h"
#include "decl/declaration.h"
#include "type/type.h"

bool Scope::insert(
	const std::string& name, const decl::Declaration_Ptr& declaration
) {
	return symbols_.insert(
		std::pair<std::string, decl::Declaration_Ptr>(name, declaration)
	).second;
}

bool Scope::insert(
	const sema::Ident_Def& id, const decl::Declaration_Ptr& declaration
) {
	declaration->exported = id.exported;
	return insert(id.ident, declaration);
}

decl::Declaration_Ptr Scope::lookup(const std::string& name) const {
	auto got { symbols_.find(name) };
	if (got != symbols_.end()) { return got->second; }
	else if (parent_) { return parent_->lookup(name); }
	else { return nullptr; }
}

void Scope::register_base_types() {
	insert("BOOLEAN", type::Type::base_boolean);
	insert("CHAR", type::Type::base_char);
	insert("INTEGER", type::Type::base_integer);
	insert("REAL", type::Type::base_real);
	insert("BYTE", type::Type::base_byte);
	insert("SET", type::Type::base_set);
}
