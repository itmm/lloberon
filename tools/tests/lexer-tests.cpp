#include "gtest/gtest.h"
#include "lexer/lexer.h"

class Lexer_String_Runner {
public:
	explicit Lexer_String_Runner(const char* source) :
		source_mgr_ { }, diag_ { source_mgr_ },
		lexer { initialize(source_mgr_, source), diag_ } { lexer.next(); }

	virtual ~Lexer_String_Runner() = default;

	virtual void run() = 0;

private:
	static llvm::SourceMgr& initialize(
		llvm::SourceMgr& source_mgr, const char* source
	) {
		source_mgr.AddNewSourceBuffer(
			llvm::MemoryBuffer::getMemBufferCopy(source), llvm::SMLoc()
		);
		return source_mgr;
	}

	llvm::SourceMgr source_mgr_;
	Diagnostics_Engine diag_;
protected:
	Lexer lexer;

	static void expect_identifier(const std::string& name) {
		EXPECT_EQ(token::kind, token::identifier);
		EXPECT_EQ(token::value, name);
	}

	static void expect_eof() {
		EXPECT_EQ(token::kind, token::eof);
	}

	static void expect_not_eof() {
		EXPECT_NE(token::kind, token::eof);
	}
};

class Single_Kind_Runner : public Lexer_String_Runner {
	token::Kind kind_;
	bool has_more_;
public:
	Single_Kind_Runner(
		const char* source, token::Kind kind, bool has_more = false
	) :
		Lexer_String_Runner { source }, kind_ { kind },
		has_more_ { has_more } { }

	void run() override {
		EXPECT_EQ(token::kind, kind_);
		lexer.next();
		if (has_more_) {
			expect_not_eof();
		} else {
			expect_eof();
		}
	}
};

void expect_empty(const char* source) {
	Single_Kind_Runner(source, token::eof).run();
}

TEST(Empty_Tests, empty_file) {
	expect_empty("");
}

TEST(Empty_Tests, only_whitespace) {
	expect_empty(" ");
	expect_empty("  ");
}

TEST(Empty_Tests, only_comments) {
	expect_empty("(* *)");
	expect_empty(" (* a *) (* b *) ");
}

class Identifiers_Runner : public Lexer_String_Runner {
	const char* first_;
	const char* second_;
public:
	Identifiers_Runner(
		const char* source, const char* first, const char* second
	) :
		Lexer_String_Runner { source }, first_ { first }, second_ { second } { }

	void run() override {
		expect_identifier(first_);
		lexer.next();
		if (second_) {
			expect_identifier(second_);
			lexer.next();
		}
		expect_eof();
	}
};

static void expect_identifiers(
	const char* source, const char* first, const char* second = nullptr
) {
	Identifiers_Runner(source, first, second).run();
}

TEST(Identifier_Tests, one_char_identifier) {
	expect_identifiers("a", "a");
	expect_identifiers("  a  ", "a");
}

TEST(Identifier_Tests, identifier_can_contain_digits) {
	expect_identifiers("a2b3", "a2b3");
}

TEST(Identifier_Tests, tab_separates_identifiers) {
	expect_identifiers("a\tb", "a", "b");
}

TEST(Identifier_Tests, newline_separates_identifiers) {
	expect_identifiers("a\nb", "a", "b");
}

TEST(Identifier_Tests, comment_separates_identifiers) {
	expect_identifiers("a(* x y *)b", "a", "b");
}

TEST(Comments_Tests, minimal_comment) {
	expect_empty("(*)");
}

TEST(Comments_Tests, nested_comments) {
	expect_empty(" (* a (* b *) c *)");
}

TEST(Comments_Tests, multiple_comments) {
	expect_empty("(*)(*) (*) ");
}

TEST(Comments_Tests, star_line) {
	expect_empty("(***)");
}

static void expect_unknown(const char* source, bool has_more = false) {
	Single_Kind_Runner(source, token::unknown, has_more).run();
}

TEST(Comments_Tests, open_comment) {
	expect_unknown("(*");
	expect_unknown("(* *");
	expect_unknown("(* (* *) ");
}

class Literal_Runner : public Lexer_String_Runner {
	token::Kind kind_;
	const char* first_;
	const char* second_;
public:
	Literal_Runner(
		const char* source, token::Kind kind,
		const char* first, const char* second
	) :
		Lexer_String_Runner { source }, kind_ { kind },
		first_ { first }, second_ { second } { }

	void run() override {
		EXPECT_EQ(token::kind, kind_);
		EXPECT_EQ(token::value, std::string(first_));
		lexer.next();
		if (second_) {
			expect_identifier(second_);
			lexer.next();
		}
		expect_eof();
	}
};

class Integer_Runner : public Literal_Runner {
public:
	Integer_Runner(const char* source, const char* first, const char* second) :
		Literal_Runner { source, token::integer_literal, first, second } { }
};

static void expect_integer(
	const char* source, const char* first = nullptr,
	const char* second = nullptr
) {
	Integer_Runner(source, first ?: source, second).run();
}

class String_Literal_Runner : public Literal_Runner {
	public:
	String_Literal_Runner(
		const char* source, const char* first, const char* second
	) :
		Literal_Runner { source, token::string_literal, first, second } { }
};

static void expect_string(const char* source) {
	String_Literal_Runner(source, source, nullptr).run();
}

class Char_Literal_Runner : public Literal_Runner {
public:
	Char_Literal_Runner(
		const char* source, const char* first, const char* second
	) :
		Literal_Runner { source, token::char_literal, first, second } { }
};

static void expect_char(
	const char* source, const char* first = nullptr,
	const char* second = nullptr
) {
	Char_Literal_Runner(source, first ?: source, second).run();
}

TEST(Integer_Tests, simple_integers) {
	expect_integer("0");
	expect_integer("00");
	expect_integer("42");
}

TEST(Integer_Tests, integer_with_identifier) {
	expect_integer("0x", "0", "x");
	expect_integer("0 x", "0", "x");
	expect_integer("0(*)x", "0", "x");
}

TEST(Integer_Tests, valid_hex) {
	expect_integer("0H");
	expect_integer("2AH");
	expect_integer("2AHH", "2AH", "H");
	expect_char("0AAX");
	expect_char("0AAXX", "0AAX", "X");
}

TEST(Integer_Tests, invalid_hex) {
	expect_unknown("2A");
}

TEST(String_Tests, simple_strings) {
	expect_string("\"12 3\"");
	expect_string("\"(*)\"");
}

TEST(String_Tests, incomplete_string) {
	expect_unknown("\"a ");
}

class Float_Literal_Runner : public Literal_Runner {
public:
	Float_Literal_Runner(
		const char* source, const char* first, const char* second
	) :
		Literal_Runner { source, token::float_literal, first, second } { }
};

void expect_float_literal(
	const char* source, const char* first = nullptr,
	const char* second = nullptr
) {
	Float_Literal_Runner { source, first ?: source, second }.run();
}

TEST(Float_Tests, simple_floats) {
	expect_float_literal("12.3");
	expect_float_literal("12.");
	expect_float_literal("12.E3");
	expect_float_literal("12.E+23");
	expect_float_literal("12.E-23");
}

TEST(Float_Tests, following_identifiers) {
	expect_float_literal("12.e", "12.", "e");
	expect_float_literal("12.E3E", "12.E3", "E");
}

TEST(Float_Tests, invalid_literals) {
	expect_unknown("12.E", false);
	expect_unknown("12.EE", true);
	expect_unknown("12.E+", false);
	expect_unknown("12.E++", true);
	expect_unknown("12.E+A", true);
	expect_unknown("12.E-", false);
}


class Integer_Range_Runner : public Lexer_String_Runner {
public:
	explicit Integer_Range_Runner(const char* source) :
		Lexer_String_Runner { source } { }

	void run() override {
		EXPECT_EQ(token::kind, token::integer_literal);
		lexer.next();
		EXPECT_EQ(token::kind, token::range);
		lexer.next();
		expect_eof();

	}
};

TEST(Integer_Range, simple) {
	Integer_Range_Runner("3..").run();
}
