#pragma once

#include "decl/declaration-with-scope.h"

namespace decl {
    class Module : public Declaration_With_Scope {
    public:
        Module(
            llvm::SMLoc loc, const std::string &name, std::string full_name
        ) :
            Declaration_With_Scope { DK_Module, nullptr, loc, name },
            full_name_{std::move(full_name)}
        {}

        [[nodiscard]] const std::string &full_name() const { return full_name_; }

        static bool classof(const Declaration *declaration) {
            return declaration && declaration->kind() == DK_Module;
        }

    private:
        const std::string full_name_;
    };
}