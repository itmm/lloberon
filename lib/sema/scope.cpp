#include "lloberon/sema/scope.h"
#include "lloberon/ast/declaration.h"

using namespace lloberon;

bool Scope::insert(lloberon::Declaration *declaration) {
    return symbols_.insert(std::pair<llvm::StringRef, Declaration*>(
            declaration->name(), declaration
    )).second;
}

Declaration* Scope::lookup(llvm::StringRef name) {
    Scope *current = this;
    while (current) {
        auto i = current->symbols_.find(name);
        if (i != current->symbols_.end()) { return i->second; }
        current = current->parent();
    }
    return nullptr;
}
