#include "lloberon/sema/scope.h"
#include "lloberon/ast/declaration.h"

using namespace lloberon;

bool Scope::insert(lloberon::Declaration *declaration) {
    if (has_in_scope(declaration->name())) { return false; }
    return symbols_.insert(std::pair<llvm::StringRef, Declaration*>(
        declaration->name(), declaration
    )).second;
}

Declaration* Scope::lookup(const std::string& name) const {
    Scope const* current = this;
    while (current) {
        auto i = current->symbols_.find(name);
        if (i != current->symbols_.end()) { return i->second; }
        current = current->parent();
    }
    return nullptr;
}

bool Scope::has_in_scope(const std::string& name) const {
    Scope const* current = this;
    while (current) {
        auto i = current->symbols_.find(name);
        if (i != current->symbols_.end()) { return true; }
        current = current->expand_ ? current->parent() : nullptr;
    }
    return false;
}

void Scope::consume(Scope& other) {
    assert(other.parent() == this && other.expand_);

    for (auto i { other.symbols_.begin() }, e { other.symbols_.end() }; i != e; ++i) {
        insert(i->second);
    }
}
