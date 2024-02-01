#pragma once

#include <ostream>

extern "C" void WriteCh(char ch);
extern "C" void WriteInt(int x, int n);
extern "C" void WriteLn();

void set_output(std::ostream& output);
void reset_output();