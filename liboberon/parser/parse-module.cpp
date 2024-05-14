#include "parser/parser.h"
#include "sema/scope.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include <llvm/IR/Module.h>

void Parser::parse_module() {
	consume(token::keyword_MODULE);
	expect(token::identifier);
	auto module_name { token::value };
	auto llvm_module { new llvm::Module { module_name, context::llvm_context } };
	context::llvm_current_module = llvm_module;

	advance();
	consume(token::semicolon);
	if (token::is(token::keyword_IMPORT)) {
		parse_import_list(*context::scope);
	}
	parse_declaration_sequence();
	context::llvm_current_function = llvm::Function::Create(
		llvm::FunctionType::get(llvm::Type::getVoidTy(context::llvm_context), false),
		llvm::GlobalValue::ExternalLinkage, module_name + "_Init_Module", *llvm_module
	);
	if (token::is(token::keyword_BEGIN)) {
		advance();
		stmt::Statement_Sequence statement_sequence {
			parse_statement_sequence()
		};
	}
	consume(token::keyword_END);
	expect(token::identifier);
	if (module_name != token::value) {
		diag::report(
			diag::err_module_names_dont_match, module_name, token::value
		);
	}
	advance();
	consume(token::period);
	expect(token::eof);

	context::llvm_current_function = nullptr;
}