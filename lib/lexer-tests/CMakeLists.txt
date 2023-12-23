set(LLVM_LINK_COMPONENTS Support)

add_lloberon_tool(lloberonLexerTests lexer-tests.cpp)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_link_libraries(lloberonLexerTests PRIVATE gtest_main lloberonBasic lloberonLexer)
