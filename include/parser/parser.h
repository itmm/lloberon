#pragma once

#include "lexer/lexer.h"
#include "llvm/Support/raw_ostream.h"
#include "sema/case.h"
#include "sema/case-list.h"
#include "sema/context.h"
#include "sema/ident-def.h"
#include "sema/label.h"
#include "sema/procedure-declaration.h"
#include "sema/scope.h"
#include "sema/statement.h"
#include "sema/statement-sequence.h"
#include "sema/qual-ident.h"
#include "type/record.h"

class Parser {
	Lexer& lexer_;

	void advance() { lexer_.next(); }

	template<typename... Args>
	[[nodiscard]] bool report(unsigned diagnostic_id, Args&& ... arguments) {
		return lexer_.report(diagnostic_id, arguments...);
	}

	[[nodiscard]] bool expect(token::Kind kind) {
		if (!token::is(kind)) {
			const char* expected = token::punctuator_spelling(kind);
			if (!expected) { expected = token::keyword_spelling(kind); }
			if (!expected) { expected = token::token_name(kind); }

			return report(diag::err_expected, expected, token::value);
		}
		return false;
	}

	[[nodiscard]] bool consume(token::Kind kind) {
		if (expect(kind)) { return true; }
		advance();
		return false;
	}

	bool check_0_int(const expr::Const& value);

public:
	explicit Parser(Lexer& lexer) : lexer_ { lexer } { advance(); }

	[[nodiscard]] bool parse();

	[[nodiscard]] bool parse_actual_parameters();

	[[nodiscard]] bool parse_array_type(type::Type_Ptr& type);

	[[nodiscard]] bool parse_assignment_or_procedure_call(
		expr::Expression_Ptr& expression
	);

	[[nodiscard]] bool parse_base_type(type::Record_Ptr& base_type);

	[[nodiscard]] bool parse_case(sema::Const_Case& const_case);

	[[nodiscard]] bool parse_case(sema::Type_Case& type_case);

	[[nodiscard]] bool parse_case_list(sema::Const_Case_List& case_list);

	[[nodiscard]] bool parse_case_list(sema::Type_Case_List& case_list);

	[[nodiscard]] bool parse_case_statement(sema::Statement& statement);

	[[nodiscard]] bool parse_const_declaration();

	[[nodiscard]] bool parse_const_expression(expr::Const_Ptr& expression);

	[[nodiscard]] bool parse_declaration_sequence();

	[[nodiscard]] bool parse_designator(expr::Expression_Ptr& designator);

	[[nodiscard]] bool parse_element(expr::Const_Ptr& expression);

	[[nodiscard]] bool parse_expression(expr::Expression_Ptr& expression);

	[[nodiscard]] bool parse_expression_list(
		expr::Expression_List& expression_list
	);

	[[nodiscard]] bool parse_factor(expr::Expression_Ptr& factor);

	[[nodiscard]] bool parse_field_list(type::Record_Ptr& record_type);

	[[nodiscard]] bool parse_field_list_sequence(type::Record_Ptr& record_type);

	[[nodiscard]] bool parse_for_statement(sema::Statement& for_statement);

	[[nodiscard]] bool parse_formal_parameter_section(
		type::Procedure_Ptr& procedure_type
	);

	[[nodiscard]] bool parse_formal_parameters(
		type::Procedure_Ptr& procedure_type
	);

	[[nodiscard]] bool parse_formal_type(type::Type_Ptr& type);

	[[nodiscard]] bool parse_ident_def(sema::Ident_Def& ident_def);

	[[nodiscard]] bool parse_ident_list(sema::Ident_List& ident_list);

	[[nodiscard]] bool parse_if_statement(sema::Statement& statement);

	[[nodiscard]] bool parse_import(Scope& scope);

	[[nodiscard]] bool parse_import_list(Scope& scope);

	[[nodiscard]] bool parse_label(expr::Const_Ptr& label);

	[[nodiscard]] bool parse_label_range(sema::Const_Label_Range& range);

	[[nodiscard]] bool parse_length(int& length);

	[[nodiscard]] bool parse_module();

	[[nodiscard]] bool parse_pointer_type(type::Type_Ptr& type);

	[[nodiscard]] bool parse_procedure_body(
		sema::Procedure_Declaration& procedure_declaration
	);

	[[nodiscard]] bool parse_procedure_declaration();

	[[nodiscard]] bool parse_procedure_heading(
		sema::Procedure_Declaration& procedure_declaration
	);

	[[nodiscard]] bool parse_procedure_type(type::Type_Ptr& type);

	[[nodiscard]] bool parse_qual_ident(sema::Qual_Ident& qual_ident);

	[[nodiscard]] bool parse_record_type(type::Type_Ptr& record_type);

	[[nodiscard]] bool parse_repeat_statement(sema::Statement& statement);

	[[nodiscard]] bool parse_set(expr::Const_Ptr& expression);

	[[nodiscard]] bool parse_simple_expression(
		expr::Expression_Ptr& expression
	);

	[[nodiscard]] bool parse_statement(sema::Statement& statement);

	[[nodiscard]] bool parse_statement_sequence(
		sema::Statement_Sequence& statement_sequence
	);

	[[nodiscard]] bool parse_term(expr::Expression_Ptr& term);

	[[nodiscard]] bool parse_type(type::Type_Ptr& type);

	[[nodiscard]] bool parse_type_declaration();

	[[nodiscard]] bool parse_variable_declaration();

	[[nodiscard]] bool parse_while_statement(sema::Statement& statement);

	[[nodiscard]] static bool is_eof() { return token::is(token::eof); }
};