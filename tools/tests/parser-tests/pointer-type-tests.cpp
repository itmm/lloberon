#include "parser-tests.h"
#include "type/pointer.h"

using Pointer_Type_Runner = Parser_Value_Runner<
	type::Type_Ptr, &Parser::parse_pointer_type
>;

TEST(Pointer_Type_Tests, empty) {
	type::Type_Ptr pointer_type;
	Pointer_Type_Runner test1 { "", pointer_type, true };
}

TEST(Pointer_Type_Tests, simple) {
	context::scope->insert("Record", std::make_shared<type::Record>());
	type::Type_Ptr pointer_type;
	Pointer_Type_Runner test1 { "POINTER TO Record", pointer_type };
	EXPECT_NE(
		std::dynamic_pointer_cast<type::Pointer>(pointer_type), nullptr
	);
	context::clear();
}

TEST(Pointer_Type_Tests, incomplete) {
	context::scope->insert("Record", std::make_shared<type::Record>());
	type::Type_Ptr pointer_type;
	Pointer_Type_Runner test1 { "POINTER TO", pointer_type, true };
	Pointer_Type_Runner test2 { "POINTER Record", pointer_type, true, true };
	context::clear();
}