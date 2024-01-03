#pragma once

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/SMLoc.h"

namespace lloberon {
    class Declaration {
    public:
        enum Kind {
            DK_Module, DK_Const, DK_Type, DK_Var, DK_Param, DK_Proc
        };

        Declaration(
            Kind kind, Declaration *enclosing_declaration,
            llvm::SMLoc loc, llvm::StringRef name
        ) :
            kind_ { kind }, enclosing_declaration_ { enclosing_declaration },
            loc_ { loc }, name_ { name }
        { }

        [[nodiscard]] Kind kind() const { return kind_; }

        [[nodiscard]] llvm::SMLoc location() { return loc_; }

        [[nodiscard]] llvm::StringRef name() { return name_; }

        [[nodiscard]] Declaration *enclosing_declaration() { return enclosing_declaration_; }

    private:
        const Kind kind_;
    protected:
        Declaration *enclosing_declaration_;
        llvm::SMLoc loc_;
        llvm::StringRef name_;
    };

    class Type_Declaration;

    class Variable_Declaration: public Declaration {
    public:
        Variable_Declaration(
            Declaration* enclosing_declaration, llvm::SMLoc loc,
            llvm::StringRef name, Type_Declaration* type
        ):
            Declaration(DK_Var, enclosing_declaration, loc, name),
            type_ { type }
        { }

        Type_Declaration* type() { return type_; }
        
        static bool class_of(const Declaration* declaration ) {
            return declaration && declaration->kind() == DK_Var;
        }

    private:
        Type_Declaration* type_;
    };
}
