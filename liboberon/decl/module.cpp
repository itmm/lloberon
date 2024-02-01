#include "decl/module.h"
#include "decl/procedure.h"
#include "sema/scope.h"
#include "basic/diagnostic.h"

decl::Module_Ptr decl::Module::system_module;
decl::Module_Ptr decl::Module::out_module;

void decl::Module::init_internal_modules() {
	if (! system_module) {
		system_module = std::make_shared<decl::Module>("SYSTEM");
	}
	if (! out_module) {
		out_module = std::make_shared<decl::Module>("Out");
		auto write_proc { std::make_shared<decl::Procedure>() };
		out_module->insert("Write", write_proc);
		auto write_int_proc { std::make_shared<decl::Procedure>() };
		out_module->insert("WriteInt", write_int_proc);
		out_module->insert("WriteLn", std::make_shared<decl::Procedure>());
	}
}

decl::Module_Ptr decl::Module::get_module(const std::string& name) {
	if (! system_module) { init_internal_modules(); }
	if (name == "SYSTEM") {
		return system_module;
	} else if (name == "Out") {
		return out_module;
	}
	diag::report(diag::err_module_not_found, name);
}
