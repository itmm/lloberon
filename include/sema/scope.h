#pragma once

#include <map>
#include <memory>
#include <string>

#include "ident-def.h"

namespace decl {
	class Declaration;
}

class Scope {
public:
	explicit Scope(const std::shared_ptr<Scope>& parent = nullptr) :
		parent_ { parent } { }

	bool insert(
		const std::string& name,
		const std::shared_ptr<decl::Declaration>& declaration
	);

	bool insert(
		const sema::Ident_Def& id,
		const std::shared_ptr<decl::Declaration>& declaration
	);

	[[nodiscard]] std::shared_ptr<decl::Declaration> lookup(
		const std::string& name
	) const;

	[[nodiscard]] std::shared_ptr<Scope> parent() const { return parent_; }

	[[nodiscard]] bool empty() const { return symbols_.empty(); }

	void clear() { symbols_.clear(); }

	void register_base_types();

private:
	std::shared_ptr<Scope> parent_;
	std::map<std::string, std::shared_ptr<decl::Declaration>> symbols_;
};