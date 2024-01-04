#pragma once

#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/StringRef.h"

namespace lloberon {
    class Declaration;
    class Scope {
    public:
        explicit Scope(Scope* parent = nullptr, bool expand = false):
            parent_ { parent }, expand_ { expand }
        { }

        bool insert(Declaration* declaration);
        [[nodiscard]] Declaration* lookup(const std::string& name) const;
        [[nodiscard]] Scope* parent() const { return parent_; }
        [[nodiscard]] bool empty() const { return symbols_.empty(); }
        void consume(Scope& other);
    private:
        Scope* parent_;
        const bool expand_;
        llvm::StringMap<Declaration*> symbols_;

        [[nodiscard]] bool has_in_scope(const std::string& name) const;
    };
}