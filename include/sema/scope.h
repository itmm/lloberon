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
	explicit Scope(Scope* parent = nullptr, bool expand = false) :
		parent_ { parent }, expand_ { expand } { }

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

	[[nodiscard]] Scope* parent() const { return parent_; }

	[[nodiscard]] bool empty() const { return symbols_.empty(); }

	void consume(Scope& other);

	void clear() { symbols_.clear(); }

private:
	[[nodiscard]] bool has_in_scope(const std::string& name) const;

	Scope* parent_;
	const bool expand_;
	std::map<std::string, std::shared_ptr<decl::Declaration>> symbols_;
};