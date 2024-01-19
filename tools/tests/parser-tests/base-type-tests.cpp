#include "parser-tests.h"
#include "type/record.h"

using Base_Type_Runner = Parser_Value_Runner<
	type::Record_Ptr, &Parser::parse_base_type
>;

TEST(Base_Type_Tests, empty) {
	context::clear();
	type::Record_Ptr base_type;
	Base_Type_Runner("", base_type, true);
}

TEST(Base_Type_Tests, simple) {
	context::clear();
	context::scope->insert("Record", std::make_shared<type::Record>());
	type::Record_Ptr base_type;
	base_type = std::make_shared<type::Record>();
	Base_Type_Runner test1("Record", base_type);
}

TEST(Base_Type_Tests, qualified) {
	context::clear();
	auto module = std::make_shared<decl::Module>("X");
	module->insert("Record", std::make_shared<type::Record>());
	context::scope->insert("X", module);
	type::Record_Ptr base_type;
	base_type = std::make_shared<type::Record>();
	Base_Type_Runner test1 { "X.Record", base_type };
}