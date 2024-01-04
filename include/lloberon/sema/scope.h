#pragma once

#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/StringRef.h"

namespace lloberon {
    class Declaration;
    class Scope {
    public:
        explicit Scope(Scope* parent = nullptr): parent_ { parent } { }
        bool insert(Declaration* declaration);
        Declaration* lookup(llvm::StringRef name);
        Scope* parent() { return parent_; }
        [[nodiscard]] bool empty() const { return symbols_.empty(); }
        [[nodiscard]] bool consume(Scope& other);
    private:
        Scope* parent_;
        llvm::StringMap<Declaration*> symbols_;
    };
}