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
	};
}