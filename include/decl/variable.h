#pragma once

#include <utility>

#include "decl/type.h"

namespace decl {
    class Variable : public Declaration {
    public:
        Variable(
            Declaration *enclosing_declaration, llvm::SMLoc loc,
            std::string name, std::shared_ptr<type::Type> type
        ) :
            Declaration(enclosing_declaration, loc, std::move(name)),
            type_ { std::move(type) }
        {}

        [[nodiscard]] std::shared_ptr<type::Type> type() const { return type_; }

    private:
        std::shared_ptr<type::Type> type_;
    };
}