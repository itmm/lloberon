#pragma once

#include "parser-tests.h"

using Type_Runner = Parser_Arg_Void_Runner<
    type::Type_Ptr, &Parser::parse_type
>;
