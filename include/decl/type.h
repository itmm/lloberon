#pragma once

#include <utility>

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/SMLoc.h"

#include "sema/scope.h"
#include "decl/declaration.h"

namespace decl {
    class Type : public Declaration {
    public:
        Type(Declaration *enclosing_declaration, llvm::SMLoc loc, std::string name) :
                Declaration(DK_Type, enclosing_declaration, loc, std::move(name)) {}

        virtual bool is_bool() { return false; }

        virtual bool is_numeric() { return false; }

        virtual bool is_integer() { return false; }

        static bool classof(const Declaration *declaration) {
            return declaration && declaration->kind() == DK_Type;
        }
    };
}