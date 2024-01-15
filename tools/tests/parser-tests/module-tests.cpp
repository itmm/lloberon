#include "parser-tests.h"
#include "decl/variable.h"

using Module_Runner = Parser_Value_Runner<Context, &Parser::parse_module>;

TEST(Module_Tests, empty) {
	Context context;
	Module_Runner test1 { "", context, true };
}

TEST(Module_Tests, simple) {
	Context context;
	Module_Runner test1 { "MODULE A; END A.", context };
}

TEST(Module_Tests, with_imports) {
	Context context;
	Module_Runner test1 { "MODULE A; IMPORT x := y; END A.", context };
}

TEST(Module_Tests, with_declarations) {
	Context context;
	Module_Runner test1 { "MODULE A; CONST B = 3; END A.", context };
}

TEST(Module_Tests, with_statements) {
	Context context;
	context.scope->insert("EXIT", std::make_shared<decl::Procedure>());
	Module_Runner test1 { "MODULE A; BEGIN EXIT(10) END A.", context };
}

TEST(Module_Tests, with_multiple) {
	auto base { std::make_shared<Scope>() };
	Context context;
	context.scope = std::make_shared<Scope>(base);
	base->insert("EXIT", std::make_shared<decl::Procedure>());
	Module_Runner test1 {
		"MODULE A; IMPORT x; CONST B = 3; BEGIN EXIT(B) END A.", context
	};

	context.scope->clear();
	Module_Runner test2 { "MODULE A; IMPORT x; CONST B = 3; END A.", context };

	context.scope->clear();
	Module_Runner test3 { "MODULE A; IMPORT x; BEGIN EXIT(10) END A.", context };

	context.scope->clear();
	Module_Runner test4 {
		"MODULE A; CONST B = 3; BEGIN EXIT(B) END A.", context
	};
}

TEST(Module_Tests, names_dont_match) {
	Context context;
	Module_Runner test1 { "MODULE A; END B.", context, true, true };
}

TEST(Module_Tests, no_semicolon) {
	Context context;
	Module_Runner test1 { "MODULE A END A.", context, true, true };
}

TEST(Module_Tests, no_period) {
	Context context;
	Module_Runner test1 { "MODULE A; END A", context, true };
}

TEST(Module_Tests, no_names) {
	Context context;
	Module_Runner test1 { "MODULE END.", context, true, true };
	Module_Runner test2 { "MODULE A END.", context, true, true };
	Module_Runner test3 { "MODULE END A.", context, true, true };
}

TEST(Module_Tests, wrong_order) {
	Context context;
	Module_Runner test1 {
		"MODULE A; CONST B = 3; IMPORT x; END A.", context, true, true
	};
}