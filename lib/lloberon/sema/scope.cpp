#include <cassert>

#include "sema/scope.h"
#include "decl/declaration.h"

bool Scope::insert(
	const std::string& name,
	const std::shared_ptr<decl::Declaration>& declaration
) {
	if (has_in_scope(name)) { return false; }
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
		current = current->parent();
	}
	return nullptr;
}

bool Scope::has_in_scope(const std::string& name) const {
	Scope const* current = this;
	while (current) {
		auto i = current->symbols_.find(name);
		if (i != current->symbols_.end()) { return true; }
		current = current->expand_ ? current->parent() : nullptr;
	}
	return false;
}

void Scope::consume(Scope& other) {
	assert(other.parent() == this && other.expand_);

	for (
		auto i { other.symbols_.begin() }, e { other.symbols_.end() };
		i != e; ++i
	) {
		insert(i->first, i->second);
	}
}
