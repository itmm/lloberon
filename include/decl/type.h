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
                Declaration(DK_Type, enclosing_declaration, loc, std::move(name)), type { std::move(type) } {}

        std::shared_ptr<type::Type> type;

        virtual bool is_bool() { return type && type->is_bool(); }

        virtual bool is_numeric() { return type && type->is_numeric(); }

        virtual bool is_integer() { return type && type->is_integer(); }

        static bool classof(const Declaration *declaration) {
            return declaration && declaration->kind() == DK_Type;
        }

        static void register_base_types(Scope& scope);
    };
}