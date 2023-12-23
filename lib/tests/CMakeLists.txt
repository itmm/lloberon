set(LLVM_LINK_COMPONENTS Support)

add_lloberon_tool(lloberonTests lexer-tests.cpp)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_link_libraries(lloberonTests PRIVATE gtest_main lloberonBasic lloberonLexer lloberonSema lloberonParser)
