#pragma once

#include <memory>
#include <utility>

#include "decl/declaration.h"
#include "type/type.h"

class Scope;

namespace decl {
    class Type : public Declaration {
    public:
        Type(Declaration *enclosing_declaration, llvm::SMLoc loc, std::string name, std::shared_ptr<type::Type> type) :
                Declaration(enclosing_declaration, loc, std::move(name)), type { std::move(type) } {}

        std::shared_ptr<type::Type> type;

        static void register_base_types(Scope& scope);
    };
}