#include "parser-tests.h"
#include "type/record.h"
#include "decl/module.h"

using Base_Type_Runner = Parser_No_Void_Runner<
	type::Record_Ptr, &Parser::parse_base_type
>;

TEST(Base_Type_Tests, empty) {
	context::clear();
	Base_Type_Runner("", true);
}

TEST(Base_Type_Tests, simple) {
	context::scope->insert("Record", std::make_shared<type::Record>());
	Base_Type_Runner test1("Record");
	context::clear();
}

TEST(Base_Type_Tests, qualified) {
	auto module = std::make_shared<decl::Module>("X");
	module->insert("Record", std::make_shared<type::Record>());
	context::scope->insert("X", module);
	Base_Type_Runner test1 { "X.Record" };
	context::clear();
}