#pragma once

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "ident-def.h"

namespace decl {
	class Declaration;
	using Declaration_Ptr = std::shared_ptr<Declaration>;
}

class Scope;

using Scope_Ptr = std::shared_ptr<Scope>;

class Scope {
public:
	explicit Scope(Scope_Ptr parent = nullptr) :
		parent_ { std::move(parent) } { }

	bool insert(
		const std::string& name, const decl::Declaration_Ptr& declaration
	);

	bool insert(
		const sema::Ident_Def& id, const decl::Declaration_Ptr& declaration
	);

	[[nodiscard]] decl::Declaration_Ptr lookup(const std::string& name) const;

	[[nodiscard]] Scope_Ptr parent() const { return parent_; }

	[[nodiscard]] bool empty() const { return symbols_.empty(); }

	void clear() { symbols_.clear(); }

	void register_base_types();

private:
	Scope_Ptr parent_;
	std::map<std::string, decl::Declaration_Ptr> symbols_;
};