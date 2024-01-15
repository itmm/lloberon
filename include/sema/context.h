#pragma once

#include <memory>

#include "scope.h"

class Context {
public:
	std::shared_ptr<Scope> scope { std::make_shared<Scope>() };
};