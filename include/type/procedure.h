#pragma once

#include "type.h"

#include <memory>
#include <string>
#include <vector>

namespace type {
	class Procedure : public Type {
	public:
		Procedure() = default;

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
	};

	using Procedure_Ptr = std::shared_ptr<Procedure>;
}