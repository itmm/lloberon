#include "parser-tests.h"
#include "decl/type.h"
#include "type/pointer.h"

using Pointer_Type_Runner = Parser_Value_Runner<
	sema::Type, &Parser::parse_pointer_type
>;

TEST(Pointer_Type_Tests, empty) {
	context::clear();
	sema::Type pointer_type;
	Pointer_Type_Runner test1 { "", pointer_type, true };
}

TEST(Pointer_Type_Tests, simple) {
	context::clear();
	context::scope->insert("Record", std::make_shared<decl::Type>(
		std::make_shared<type::Record>()
	));
	sema::Type pointer_type;
	Pointer_Type_Runner test1 { "POINTER TO Record", pointer_type };
	EXPECT_NE(
		std::dynamic_pointer_cast<type::Pointer>(pointer_type.type), nullptr
	);
}

TEST(Pointer_Type_Tests, incomplete) {
	context::clear();
	context::scope->insert("Record", std::make_shared<decl::Type>(
		std::make_shared<type::Record>()
	));
	sema::Type pointer_type;
	Pointer_Type_Runner test1 { "POINTER TO", pointer_type, true };
	Pointer_Type_Runner test2 { "POINTER Record", pointer_type, true, true };
}