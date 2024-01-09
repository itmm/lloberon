#pragma once

#include <utility>
#include <string>

#include "llvm/Support/SMLoc.h"

namespace decl {
    class Declaration {
    public:
        Declaration(
            Declaration *enclosing_declaration,
            llvm::SMLoc loc, std::string name
        ) :
            enclosing_declaration_{enclosing_declaration},
            loc_{loc}, name_{std::move(name)} {}

        virtual ~Declaration() = default;

        [[nodiscard]] llvm::SMLoc location() const { return loc_; }

        [[nodiscard]] std::string name() const { return name_; }

        [[nodiscard]] const Declaration *enclosing_declaration() const {
            return enclosing_declaration_;
        }

    protected:
        const Declaration *enclosing_declaration_;
        const llvm::SMLoc loc_;
        const std::string name_;
    };
}