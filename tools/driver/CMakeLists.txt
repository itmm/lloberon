set(LLVM_LINK_COMPONENTS Support)

add_lloberon_tool(lloberon driver.cpp)

target_link_libraries(lloberon PRIVATE liboberon)

