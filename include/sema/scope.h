#pragma once

#include <map>
#include <memory>
#include <string>

class Declaration;

class Scope {
public:
    explicit Scope(Scope* parent = nullptr, bool expand = false):
        parent_ { parent }, expand_ { expand }
    { }

    bool insert(const std::shared_ptr<Declaration>& declaration);
    [[nodiscard]] std::shared_ptr<Declaration> lookup(const std::string& name) const;
    [[nodiscard]] Scope* parent() const { return parent_; }
    [[nodiscard]] bool empty() const { return symbols_.empty(); }
    void consume(Scope& other);
private:
    Scope* parent_;
    const bool expand_;
    std::map<std::string, std::shared_ptr<Declaration>> symbols_;

    [[nodiscard]] bool has_in_scope(const std::string& name) const;
};