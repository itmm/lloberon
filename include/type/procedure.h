#pragma once

#include "type.h"
#include "decl/declaration-with-scope.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace type {
	class Procedure;

	using Procedure_Ptr = std::shared_ptr<Procedure>;

	class Procedure : public Type {
	public:
		Procedure(): Type { nullptr } { }

		Type_Ptr return_type;

		struct Parameter {
			Parameter(std::string name, Type_Ptr type, bool reference) :
				name { std::move(name) }, type { std::move(type) },
				reference { reference } { }

			const std::string name;
			Type_Ptr type;
			bool reference;
		};

		std::vector<Parameter> parameters;

		static Procedure_Ptr as_procedure(const decl::Declaration_Ptr& decl) {
			return std::dynamic_pointer_cast<Procedure>(decl);
		}
	};

	class External_Procedure: public Procedure, public decl::Scope_Mixin {
	public:
		explicit External_Procedure(std::string external_name):
			external_name { std::move(external_name) }
		{ }

		const std::string external_name;
	};
}