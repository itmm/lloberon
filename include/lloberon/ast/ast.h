#pragma once

#include <utility>

#include "lloberon/basic/token-kinds.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/SMLoc.h"

class AST;
class Expression;
class Factor;
class Binary_Operator;

class AST_Visitor {
public:
    virtual ~AST_Visitor() = default;

    virtual void visit(AST&) { }
    virtual void visit(Expression&) { }
    virtual void visit(Factor&) = 0;
    virtual void visit(Binary_Operator&) = 0;
};

class AST {
public:
    virtual ~AST() = default;
    virtual void accept(AST_Visitor& visitor) = 0;
};

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
                kind_{kind}, enclosing_declaration_{enclosing_declaration},
                loc_{loc}, name_{name} {}

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

class Expression: public AST {
public:
    Expression() = default;
};

class Factor: public Expression {
public:
    Factor(lloberon::token::Kind kind, llvm::StringRef value): kind_ { kind }, value_ { value } { }

    [[nodiscard]] lloberon::token::Kind kind() const { return kind_; }
    [[nodiscard]] llvm::StringRef value() const { return value_; }

    void accept(AST_Visitor& visitor) override {
        visitor.visit(*this);
    }

private:
    lloberon::token::Kind kind_;
    llvm::StringRef value_;
};

class Binary_Operator: public Expression {
public:
    Binary_Operator(lloberon::token::Kind op, Expression* left, Expression* right):
            left_ { left }, right_ { right }, op_ { op }
    { }

    [[nodiscard]] Expression* left() const { return left_; }
    [[nodiscard]] Expression* right() const { return right_; }
    [[nodiscard]] lloberon::token::Kind op() const { return op_; }

    void accept(AST_Visitor& visitor) override {
        visitor.visit(*this);
    }

private:
    Expression* left_;
    Expression* right_;
    lloberon::token::Kind op_;
};
