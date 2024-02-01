#include <unistd.h>
#include <iostream>
#include <limits>

static std::ostream* out { &std::cout };

extern "C" void WriteCh(char ch) { *out << ch; }

extern "C" void WriteInt(int x, int n) {
	int i { 0 };
	char a[std::numeric_limits<int>::digits10 + 1];
	bool negative { x < 0 };
	if (negative) { --n; a[i++] = -(x % 10); x = -(x / 10); }
	else { a[i++] = x % 10; x /= 10; }
	while (x > 0) { a[i++] = x % 10; x /= 10; }

	while (n > i) { WriteCh(' '); --n; }
	if (negative) { WriteCh('-'); }
	do { --i; WriteCh(a[i] + '0'); } while (i > 0);
}

extern "C" void WriteLn() { WriteCh('\n'); }

void set_output(std::ostream& output) { out = &output; }
void reset_output() { out = &std::cout; }
