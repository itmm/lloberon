#include "parser-tests.h"
#include "decl/type.h"
#include "type/record.h"

using Base_Type_Runner = Parser_Value_Runner<
	sema::Record_Type, &Parser::parse_base_type
>;

TEST(Base_Type_Tests, empty) {
	Context context;
	sema::Record_Type base_type { context };
	Base_Type_Runner("", base_type, true);
}

TEST(Base_Type_Tests, simple) {
	Context context;
	context.scope->insert("Record", std::make_shared<decl::Type>(
		std::make_shared<type::Record>()
	));
	sema::Record_Type base_type { context };
	Base_Type_Runner test1("Record", base_type);
}

TEST(Base_Type_Tests, qualified) {
	Context context;
	auto module = std::make_shared<decl::Module>("X");
	module->insert("Record", std::make_shared<decl::Type>(
		std::make_shared<type::Record>()
	));
	context.scope->insert("X", module);
	sema::Record_Type base_type { context };
	Base_Type_Runner test1 { "X.Record", base_type };
}