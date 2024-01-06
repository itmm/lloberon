#pragma once

#include <utility>

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/SMLoc.h"

#include "sema/scope.h"
#include "decl/type.h"

namespace decl {
    class Base_Type : public Type {
    public:
        enum Kind {
            bt_BOOLEAN, bt_CHAR, bt_INTEGER, bt_REAL, bt_BYTE, bt_SET
        };

        static void register_base_types(Scope &scope);

        Base_Type(
                std::string name, Kind kind
        ) :
                Type(nullptr, llvm::SMLoc{}, std::move(name)),
                kind_{kind} {}

        bool is_bool() override { return kind_ == bt_BOOLEAN; }

        bool is_numeric() override {
            return kind_ == bt_INTEGER || kind_ == bt_REAL || kind_ == bt_BYTE;
        }

        bool is_integer() override { return kind_ == bt_INTEGER || kind_ == bt_BYTE; }

        [[nodiscard]] Kind base_kind() const { return kind_; }

    private:
        const Kind kind_;
    };
}