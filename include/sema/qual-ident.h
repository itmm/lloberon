#pragma once

#include "scope.h"
#include "decl/module.h"
#include "decl/variable.h"
#include "expr/variable.h"
#include "expr/procedure.h"

namespace sema {
	class Qual_Ident {
	public:
		explicit Qual_Ident(Context& context) : context { context } { }

		Context& context;

		std::shared_ptr<decl::Declaration> declaration { nullptr };
		std::shared_ptr<decl::Module> module { nullptr };

		[[nodiscard]] std::shared_ptr<type::Type> as_type() const {
			auto decl { std::dynamic_pointer_cast<decl::Type>(declaration) };
			return decl ? decl->type : nullptr;
		}

		[[nodiscard]] std::shared_ptr<expr::Variable> as_variable() const {
			auto decl { std::dynamic_pointer_cast<decl::Variable>(
				declaration
			) };
			return decl ?
				std::make_shared<expr::Variable>(decl->type()) : nullptr;
		}

		[[nodiscard]] std::shared_ptr<expr::Procedure> as_procedure() const {
			auto decl { std::dynamic_pointer_cast<decl::Procedure>(
				declaration
			) };
			return decl ?
				std::make_shared<expr::Procedure>(decl->type) : nullptr;
		}
	};
}