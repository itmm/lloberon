#pragma once

#include <utility>

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/SMLoc.h"

#include "sema/scope.h"

namespace decl {
    class Declaration {
    public:
        enum Kind {
            DK_Module, DK_Const, DK_Type, DK_Var, DK_Param, DK_Proc
        };

        Declaration(
                Kind kind, Declaration *enclosing_declaration,
                llvm::SMLoc loc, std::string name
        ) :
                kind_{kind}, enclosing_declaration_{enclosing_declaration},
                loc_{loc}, name_{std::move(name)} {}

        virtual ~Declaration() = default;

        [[nodiscard]] Kind kind() const { return kind_; }

        [[nodiscard]] llvm::SMLoc location() const { return loc_; }

        [[nodiscard]] std::string name() const { return name_; }

        [[nodiscard]] const Declaration *enclosing_declaration() const { return enclosing_declaration_; }

    private:
        const Kind kind_;
    protected:
        const Declaration *enclosing_declaration_;
        const llvm::SMLoc loc_;
        const std::string name_;
    };
}