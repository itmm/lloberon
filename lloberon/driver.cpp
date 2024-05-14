#include "basic/diagnostic.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

#include "llvm/ADT/Optional.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/ErrorOr.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/WithColor.h"
#include "llvm/TargetParser/Triple.h"
#include "llvm/CodeGen/CommandFlags.h"
#include "llvm/MC/TargetRegistry.h"

static llvm::codegen::RegisterCodeGenFlags CGF;

int main(int argc, const char** argv) {
	llvm::InitLLVM X(argc, argv);

	enum Generate { gen_ir, gen_asm, gen_obj, gen_exe } generate { gen_ir };
	std::string target { };

	auto i { argv + 1 }, e { argv + argc };
	for (; i < e; ++i) {
		std::string arg { *i };
		if (arg == "--ir") { generate = gen_ir; }
		else if (arg == "--asm") { generate = gen_asm; }
		else if (arg == "--obj") { generate = gen_obj; }
		else if (arg == "--exe") { generate = gen_exe; }
		else if (arg.find("--target=") == 0) { target = arg.substr(9); }
		else if (**i == '-') {
			std::cerr << "unknown option `" << *i << "'\n";
			return 10;
		} else { break; }
	}

	llvm::InitializeAllTargets();
	llvm::InitializeAllTargetMCs();
	llvm::InitializeAllAsmPrinters();
	llvm::InitializeAllAsmParsers();

	llvm::Triple llvm_triple { !target.empty() ? llvm::Triple::normalize(target) : llvm::sys::getDefaultTargetTriple() };
	auto llvm_target_options { llvm::codegen::InitTargetOptionsFromCodeGenFlags(llvm_triple) };

	std::string Error;
	const llvm::Target *Target =
		llvm::TargetRegistry::lookupTarget(llvm::codegen::getMArch(), llvm_triple, Error);

	if (!Target) {
		llvm::WithColor::error(llvm::errs(), argv[0]) << Error;
		return 10;
	}

	auto triple { llvm_triple.getTriple() };
	auto cpu_str { llvm::codegen::getCPUStr() };
	auto feature_str { llvm::codegen::getFeaturesStr() };
	/*
	context::llvm_target_machine = Target->createTargetMachine(
		triple, cpu_str, feature_str, llvm_target_options,
		llvm::Optional<llvm::Reloc::Model>(llvm::codegen::getRelocModel()));
	if (! context::llvm_target_machine) { return 10; }
	*/

	for (; i < e; ++i) {
		llvm::outs() << "parsing " << *i << "\n";
		llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>> file_or_error =
			llvm::MemoryBuffer::getFile(*i);
		if (std::error_code buffer_error = file_or_error.getError()) {
			llvm::errs() << "Error reading " << *i << ": "
						 << buffer_error.message() << "\n";
			continue;
		}

		llvm::SourceMgr source_mgr;
		source_mgr.AddNewSourceBuffer(std::move(*file_or_error), llvm::SMLoc());
		Lexer lexer { source_mgr };
		Parser parser { lexer };
		try {
			parser.parse();
			if (generate == gen_ir) {
				if (context::llvm_current_module) {
					context::llvm_current_module->print(llvm::outs(), nullptr);
				} else {
					llvm::errs() << "NO MODULE DEFINED\n";
				}
			}
		} catch (const diag::Error& error) {
			source_mgr.PrintMessage(
				llvm::SMLoc::getFromPointer(token::source),
				llvm::SourceMgr::DK_Error, error.what()
			);
			return 10;
		}
	}
	return 0;
}

