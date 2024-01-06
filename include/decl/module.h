#pragma once

#include <utility>

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/SMLoc.h"

#include "sema/scope.h"
#include "decl/declaration.h"

namespace decl {
    class Module : public Declaration {
    public:
        Module(
                llvm::SMLoc loc, const std::string &name, std::string full_name
        ) :
                Declaration(DK_Module, nullptr, loc, name),
                full_name_{std::move(full_name)} {}

        [[nodiscard]] const std::string &full_name() const { return full_name_; }

        static bool classof(const Declaration *declaration) {
            return declaration && declaration->kind() == DK_Module;
        }

        std::shared_ptr<decl::Declaration> lookup(const std::string &name) {
            return scope_.lookup(name);
        }

        bool insert(const std::shared_ptr<decl::Declaration> &declaration) {
            return scope_.insert(declaration);
        }

    private:
        const std::string full_name_;
        Scope scope_;
    };
}