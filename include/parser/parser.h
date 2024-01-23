#pragma once

#include "lexer/lexer.h"
#include "sema/case-list.h"
#include "sema/case.h"
#include "sema/context.h"
#include "sema/ident-def.h"
#include "sema/label.h"
#include "sema/procedure-declaration.h"
#include "sema/scope.h"
#include "stmt/for.h"
#include "type/record.h"
#include "llvm/Support/raw_ostream.h"

class Parser {
	Lexer& lexer_;

	void advance() { lexer_.next(); }

	static void expect(token::Kind kind) {
		if (!token::is(kind)) {
			const char* expected = token::punctuator_spelling(kind);
			if (!expected) { expected = token::keyword_spelling(kind); }
			if (!expected) { expected = token::token_name(kind); }

			diag::report(diag::err_expected, expected, token::value);
		}
	}

	void consume(token::Kind kind) {
		expect(kind);
		advance();
	}

	static void check_0_int(const expr::Const& value);

public:
	explicit Parser(Lexer& lexer) : lexer_ { lexer } { advance(); }

	void parse();

	void parse_actual_parameters();

	[[nodiscard]] type::Array_Ptr parse_array_type();

	void parse_assignment_or_procedure_call(expr::Expression_Ptr& expression);

	[[nodiscard]] type::Record_Ptr parse_base_type();

	void parse_case(sema::Const_Case& const_case);

	void parse_case(sema::Type_Case& type_case);

	void parse_case_list(sema::Const_Case_List& case_list);

	void parse_case_list(sema::Type_Case_List& case_list);

	[[nodiscard]] stmt::Statement_Ptr parse_case_statement();

	void parse_const_declaration();

	[[nodiscard]] expr::Const_Ptr parse_const_expression();

	void parse_declaration_sequence();

	[[nodiscard]] expr::Expression_Ptr parse_designator();

	void parse_element(unsigned& set_value);

	[[nodiscard]] expr::Expression_Ptr parse_expression();

	[[nodiscard]] expr::Expression_List parse_expression_list();

	[[nodiscard]] expr::Expression_Ptr parse_factor();

	void parse_field_list(type::Record& record_type);

	void parse_field_list_sequence(type::Record& record_type);

	stmt::For_Ptr parse_for_statement();

	void parse_formal_parameter_section(type::Procedure_Ptr& procedure_type);

	void parse_formal_parameters(type::Procedure_Ptr& procedure_type);

	void parse_formal_type(type::Type_Ptr& type);

	void parse_ident_def(sema::Ident_Def& ident_def);

	void parse_ident_list(sema::Ident_List& ident_list);

	void parse_if_statement(stmt::Statement_Ptr& statement);

	void parse_import(Scope& scope);

	void parse_import_list(Scope& scope);

	void parse_label(expr::Const_Ptr& label);

	void parse_label_range(sema::Const_Label_Range& range);

	[[nodiscard]] int parse_length();

	void parse_module();

	void parse_pointer_type(type::Type_Ptr& type);

	void parse_procedure_body(
		sema::Procedure_Declaration& procedure_declaration
	);

	void parse_procedure_declaration();

	void parse_procedure_heading(
		sema::Procedure_Declaration& procedure_declaration
	);

	void parse_procedure_type(type::Type_Ptr& type);

	[[nodiscard]] decl::Declaration_Ptr parse_qual_ident();

	[[nodiscard]] type::Record_Ptr parse_record_type();

	void parse_repeat_statement(stmt::Statement_Ptr& statement);

	void parse_set(expr::Const_Ptr& expression);

	[[nodiscard]] expr::Expression_Ptr parse_simple_expression();

	void parse_statement(stmt::Statement_Ptr& statement);

	void parse_statement_sequence(stmt::Statement_Sequence& statement_sequence);

	[[nodiscard]] expr::Expression_Ptr parse_term();

	void parse_type(type::Type_Ptr& type);

	void parse_type_declaration();

	void parse_variable_declaration();

	void parse_while_statement(stmt::Statement_Ptr& statement);

	[[nodiscard]] static bool is_eof() { return token::is(token::eof); }
};