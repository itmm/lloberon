#pragma once

#include <utility>

#include "lloberon/basic/token-kinds.h"
#include "llvm/ADT/StringRef.h"

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

class Expression: public AST {
public:
    Expression() = default;
};

class Factor: public Expression {
public:
    Factor(lloberon::token::Token_Kind kind, llvm::StringRef value): kind_ { kind }, value_ { value } { }

    [[nodiscard]] lloberon::token::Token_Kind kind() const { return kind_; }
    [[nodiscard]] llvm::StringRef value() const { return value_; }

    void accept(AST_Visitor& visitor) override {
        visitor.visit(*this);
    }

private:
    lloberon::token::Token_Kind kind_;
    llvm::StringRef value_;
};

class Binary_Operator: public Expression {
public:
    Binary_Operator(lloberon::token::Token_Kind op, Expression* left, Expression* right):
            left_ { left }, right_ { right }, op_ { op }
    { }

    [[nodiscard]] Expression* left() const { return left_; }
    [[nodiscard]] Expression* right() const { return right_; }
    [[nodiscard]] lloberon::token::Token_Kind op() const { return op_; }

    void accept(AST_Visitor& visitor) override {
        visitor.visit(*this);
    }

private:
    Expression* left_;
    Expression* right_;
    lloberon::token::Token_Kind op_;
};
