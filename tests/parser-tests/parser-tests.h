#pragma once

#include "gtest/gtest.h"
#include "parser/parser.h"

template<void (Parser::*METHOD)()>
class Parser_No_Arg_Void_Runner {
public:
	explicit Parser_No_Arg_Void_Runner(
		const char* source, bool expected = false, bool has_more = false,
		bool verbose = false
	):
		source_mgr_ { }, lexer_ { initialize(source_mgr_, source) },
		expected_ { expected }, has_more_ { has_more }, parser_ { lexer_ },
		verbose_ { verbose }
	{ run(); }

	void run() {
		bool failed;
		try {
			(parser_.*METHOD)();
			failed = false;
		}
		catch (const diag::Error& err) {
			if (verbose_) { std::cerr << err.what() << "\n"; }
			failed = true;
		}

		if (expected_) {
			EXPECT_TRUE(failed);
		} else {
			EXPECT_FALSE(failed);
		}
		if (has_more_) {
			EXPECT_FALSE(parser_.is_eof());
		} else {
			EXPECT_TRUE(parser_.is_eof());
		}

	}

private:
	static llvm::SourceMgr& initialize(llvm::SourceMgr& source_mgr, const char* source) {
		source_mgr.AddNewSourceBuffer(
			llvm::MemoryBuffer::getMemBufferCopy(source),
			llvm::SMLoc()
		);
		return source_mgr;
	}
	llvm::SourceMgr source_mgr_;
	Lexer lexer_;
	bool expected_;
	bool has_more_;
	Parser parser_;
	bool verbose_;
};

template<typename VALUE, VALUE (Parser::*METHOD)()>
class Parser_No_Void_Runner {
	public:
	explicit Parser_No_Void_Runner(
		const char* source, bool expected = false, bool has_more = false,
		bool verbose = false
	):
		source_mgr_ { }, lexer_ { initialize(source_mgr_, source) },
		expected_ { expected }, has_more_ { has_more }, parser_ { lexer_ },
		verbose_ { verbose }
	{ run(); }

	void run() {
		bool failed;
		try {
			value = (parser_.*METHOD)();
			failed = false;
		}
		catch (const diag::Error& err) {
			if (verbose_) { std::cerr << err.what() << "\n"; }
			failed = true;
		}
		if (expected_) {
			EXPECT_TRUE(failed);
		} else {
			EXPECT_FALSE(failed);
		}
		if (has_more_) {
			EXPECT_FALSE(parser_.is_eof());
		} else {
			EXPECT_TRUE(parser_.is_eof());
		}

	}

	VALUE value;

private:
	static llvm::SourceMgr& initialize(llvm::SourceMgr& source_mgr, const char* source) {
		source_mgr.AddNewSourceBuffer(
			llvm::MemoryBuffer::getMemBufferCopy(source),
			llvm::SMLoc()
		);
		return source_mgr;
	}
	llvm::SourceMgr source_mgr_;
	Lexer lexer_;
	bool expected_;
	bool has_more_;
	Parser parser_;
	bool verbose_;
};
template<typename VALUE, void (Parser::*METHOD)(VALUE&)>
class Parser_Arg_Void_Runner {
public:
	explicit Parser_Arg_Void_Runner(
		const char* source, VALUE& value, bool expected = false,
		bool has_more = false, bool verbose = false
	):
		source_mgr_ { }, lexer_ { initialize(source_mgr_, source) },
		expected_ { expected }, has_more_ { has_more },
		parser_ { lexer_ }, value_ { value }, verbose_ { verbose }
	{ run(); }

	void run() {
		bool failed;
		try {
			(parser_.*METHOD)(value_);
			failed = false;
		}
		catch (const diag::Error& err) {
			if (verbose_) { std::cerr << err.what() << "\n"; }
			failed = true;
		}
		if (expected_) {
			EXPECT_TRUE(failed);
		} else {
			EXPECT_FALSE(failed);
		}
		if (has_more_) {
			EXPECT_FALSE(parser_.is_eof());
		} else {
			EXPECT_TRUE(parser_.is_eof());
		}

	}

private:
	static llvm::SourceMgr& initialize(llvm::SourceMgr& source_mgr, const char* source) {
		source_mgr.AddNewSourceBuffer(
			llvm::MemoryBuffer::getMemBufferCopy(source),
			llvm::SMLoc()
		);
		return source_mgr;
	}
	llvm::SourceMgr source_mgr_;
	Lexer lexer_;
	bool expected_;
	bool has_more_;
	Parser parser_;
	VALUE& value_;
	bool verbose_;
};
