#include "parser-tests.h"
#include "decl/variable.h"

using Module_Runner = Parser_String_Runner<&Parser::parse_module>;

TEST(Module_Tests, empty) {
	Module_Runner test1 { "", true };
}

TEST(Module_Tests, simple) {
	Module_Runner test1 { "MODULE A; END A." };
}

TEST(Module_Tests, with_imports) {
	Module_Runner test1 { "MODULE A; IMPORT x := y; END A." };
	context::clear();
}

TEST(Module_Tests, with_declarations) {
	Module_Runner test1 { "MODULE A; CONST B = 3; END A." };
	context::clear();
}

TEST(Module_Tests, with_statements) {
	context::scope->insert("EXIT", std::make_shared<decl::Procedure>());
	Module_Runner test1 { "MODULE A; BEGIN EXIT(10) END A." };
	context::clear();
}

TEST(Module_Tests, with_multiple) {
	auto base { std::make_shared<Scope>() };
	context::scope = std::make_shared<Scope>(base);
	base->insert("EXIT", std::make_shared<decl::Procedure>());
	Module_Runner test1 {
		"MODULE A; IMPORT x; CONST B = 3; BEGIN EXIT(B) END A."
	};
	context::scope->clear();

	Module_Runner test2 { "MODULE A; IMPORT x; CONST B = 3; END A." };
	context::scope->clear();

	Module_Runner test3 { "MODULE A; IMPORT x; BEGIN EXIT(10) END A." };
	context::scope->clear();

	Module_Runner test4 { "MODULE A; CONST B = 3; BEGIN EXIT(B) END A." };
	context::clear();
}

TEST(Module_Tests, names_dont_match) {
	Module_Runner test1 { "MODULE A; END B.", true, true };
}

TEST(Module_Tests, no_semicolon) {
	Module_Runner test1 { "MODULE A END A.", true, true };
}

TEST(Module_Tests, no_period) {
	Module_Runner test1 { "MODULE A; END A", true };
}

TEST(Module_Tests, no_names) {
	Module_Runner test1 { "MODULE END.", true, true };
	Module_Runner test2 { "MODULE A END.", true, true };
	Module_Runner test3 { "MODULE END A.", true, true };
}

TEST(Module_Tests, wrong_order) {
	Module_Runner test1 {
		"MODULE A; CONST B = 3; IMPORT x; END A.", true, true
	};
}