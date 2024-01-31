#include "parser-tests.h"
#include "type/pointer.h"

using Pointer_Type_Runner = Parser_No_Void_Runner<
	type::Pointer_Ptr, &Parser::parse_pointer_type
>;

TEST(Pointer_Type_Tests, empty) {
	Pointer_Type_Runner test1 { "", true };
}

TEST(Pointer_Type_Tests, simple) {
	context::scope->insert("Record", std::make_shared<type::Record>());
	Pointer_Type_Runner test1 { "POINTER TO Record" };
	EXPECT_NE(test1.value, nullptr);
	context::clear();
}

TEST(Pointer_Type_Tests, incomplete) {
	context::scope->insert("Record", std::make_shared<type::Record>());
	Pointer_Type_Runner test1 { "POINTER TO", true };
	Pointer_Type_Runner test2 { "POINTER Record", true, true };
	context::clear();
}