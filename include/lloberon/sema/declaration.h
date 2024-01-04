#pragma once

#include <utility>

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/SMLoc.h"

#include "scope.h"

namespace lloberon {
    class Declaration {
    public:
        enum Kind {
            DK_Module, DK_Const, DK_Type, DK_Var, DK_Param, DK_Proc
        };

        Declaration(
            Kind kind, Declaration *enclosing_declaration,
            llvm::SMLoc loc, std::string  name
        ) :
            kind_ { kind }, enclosing_declaration_ { enclosing_declaration },
            loc_ { loc }, name_ { std::move(name) }
        { }

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

    class Module_Declaration: public Declaration {
    public:
        Module_Declaration(
            llvm::SMLoc loc, const std::string& name, std::string full_name
        ):
            Declaration(DK_Module, nullptr, loc, name),
            full_name_ { std::move(full_name) }
        { }

        [[nodiscard]] const std::string& full_name() const { return full_name_; }

        static bool classof(const Declaration* declaration ) {
            return declaration && declaration->kind() == DK_Module;
        }

        Declaration* lookup(const std::string& name) {
            return scope_.lookup(name);
        }

        bool insert(Declaration* decl) {
            return scope_.insert(decl);
        }

    private:
        const std::string full_name_;
        Scope scope_;
    };

    class Type_Declaration: public Declaration {
    public:
        Type_Declaration(Declaration* enclosing_declaration, llvm::SMLoc loc, std::string name):
            Declaration(DK_Type, enclosing_declaration, loc, std::move(name))
        { }

        virtual bool is_bool() { return false; }
        virtual bool is_numeric() { return false; }
        virtual bool is_integer() { return false; }

        static bool classof(const Declaration* declaration ) {
            return declaration && declaration->kind() == DK_Type;
        }
    };

    class Base_Type_Declaration: public Type_Declaration {
    public:
        enum Kind { bt_BOOLEAN, bt_CHAR, bt_INTEGER, bt_REAL, bt_BYTE, bt_SET };

        Base_Type_Declaration(
            std::string name, Kind kind
        ):
            Type_Declaration(nullptr, llvm::SMLoc { }, std::move(name)),
            kind_ { kind }
        { }

        bool is_bool() override { return kind_ == bt_BOOLEAN; }
        bool is_numeric() override {
            return kind_ == bt_INTEGER || kind_ == bt_REAL || kind_ == bt_BYTE;
        }
        bool is_integer() override { return kind_ == bt_INTEGER || kind_ == bt_BYTE; }

        [[nodiscard]] Kind base_kind() const { return kind_; }

    private:
        const Kind kind_;
    };

    class Variable_Declaration: public Declaration {
    public:
        Variable_Declaration(
            Declaration* enclosing_declaration, llvm::SMLoc loc,
            std::string name, Type_Declaration* type
        ):
            Declaration(DK_Var, enclosing_declaration, loc, std::move(name)),
            type_ { type }
        { }

        Type_Declaration* type() { return type_; }
        
        static bool classof(const Declaration* declaration ) {
            return declaration && declaration->kind() == DK_Var;
        }

    private:
        Type_Declaration* type_;
    };
}
