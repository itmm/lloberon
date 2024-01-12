#pragma once

#include <memory>
#include <utility>

#include "decl/declaration.h"
#include "expr/const.h"

class Scope;

namespace decl {
	class Const : public Declaration {
	public:
		explicit Const(std::shared_ptr<expr::Const> value) :
			Declaration { }, value { std::move(value) } { }

		std::shared_ptr<expr::Const> value;

		static std::shared_ptr<expr::Const> as_const(
			const std::shared_ptr<Declaration>& declaration
		) {
			auto const_decl { std::dynamic_pointer_cast<Const>(declaration) };
			if (const_decl) {
				return const_decl->value;
			}
			return nullptr;
		}
	};
}