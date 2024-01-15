#include <cassert>

#include "sema/scope.h"
#include "decl/declaration.h"

bool Scope::insert(
	const std::string& name,
	const std::shared_ptr<decl::Declaration>& declaration
) {
	return symbols_.insert(
		std::pair<std::string, std::shared_ptr<decl::Declaration>>(
			name, declaration
		)
	).second;
}

bool Scope::insert(
	const sema::Ident_Def& id,
	const std::shared_ptr<decl::Declaration>& declaration
) {
	declaration->exported = id.exported;
	return insert(id.ident, declaration);
}

std::shared_ptr<decl::Declaration> Scope::lookup(
	const std::string& name
) const {
	Scope const* current = this;
	while (current) {
		auto i = current->symbols_.find(name);
		if (i != current->symbols_.end()) { return i->second; }
		current = current->parent().get();
	}
	return nullptr;
}
