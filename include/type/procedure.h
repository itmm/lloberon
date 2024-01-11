#pragma once

#include "type.h"

#include <memory>
#include <string>
#include <vector>

namespace type {
	class Procedure : public Type {
	public:
		Procedure() = default;

		std::shared_ptr<Type> return_type;

		struct Parameter {
			Parameter(
				std::string name, std::shared_ptr<type::Type> type,
				bool reference
			) :
				name { std::move(name) }, type { std::move(type) },
				reference { reference } { }

			const std::string name;
			std::shared_ptr<type::Type> type;
			bool reference;
		};

		std::vector<Parameter> parameters;
	};
}